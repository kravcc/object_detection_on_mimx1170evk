// This file is a combination of my code and the code from the sources

/*
 * Autor: Marina Kravchuk
 */

/*
 * Copyright 2024  NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * "NXP code"
 */

/*
 * Copyright (c) 2022 EdgeImpulse Inc.
 *
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * "Edge Impulse code"
 */

#include "board_init.h"
#include "demo_config.h"
#include "fsl_debug_console.h"
#include "image.h"
#include "image_utils.h"
#include "model.h"
#include "output_postproc.h"
#include "timer.h"

#include "eiq_video_worker.h"

#include "tcpsrv.h"


#include "lwip/opt.h"

#if LWIP_NETCONN

#include "lwip/sys.h"
#include "lwip/api.h"

#include "string.h"

#define SERVER_PORT 7
#define RECV_TIMEOUT_MS 1000
#define ACK_LENGTH 4
#define MESSAGE_LENGTH 64

char ack[ACK_LENGTH] = "ACK";

float output[96*96];

uint8_t result_array[64] = {0};
enum Item {
	BACKGROUND,
	BLUE_CIRCLE,
	BLUE_SQUARE,
	BLUE_STAR,
	GREEN_CIRCLE,
	GREEN_SQUARE,
	GREEN_STAR,
	ORANGE_CIRCLE,
	ORANGE_SQUARE,
	ORANGE_STAR
};


/* Edge Impulse code
 *
 * @brief Callback: fill a section of the out_ptr buffer when requested
 */
static int get_signal_data(size_t offset, size_t length, float *out_ptr) {
    for (size_t i = 0; i < length; i++) {
        out_ptr[i] = (output + offset)[i];
    }

    return kStatus_Success;
}
/*
 * Edge Impulse code end
 */


/*
 * NXP code
 *
 * @brief Send message to the client
 *
 * @param buf_write Network buffer
 * @param conn Socket adress
 * @param message Message text
 * @param size Size of the message
 */
static void tcpsrv_sendMessage(struct netbuf *buf_write, struct netconn *conn, char *message, u16_t size)
{
	err_t err;
	void *data;
	u16_t len;

	// my modification
	if (!(strcmp(message,"ACK")))
		err = netbuf_ref(buf_write, message, size);
	else
		err = netbuf_ref(buf_write, result_array, size);
	// modification end

	LWIP_ERROR("tcp server: buffer assignment failed\n\r", (err == ERR_OK), return;);

	buf_write->port = 0;
	ip_addr_set_zero(&buf_write->addr);

	do {
		netbuf_data(buf_write, &data, &len);
		err = netconn_write(conn, data, len, NETCONN_COPY);
		LWIP_ERROR("tcp server: write failed\n\r", err == ERR_OK, lwip_strerr(err));
	} while (netbuf_next(buf_write) >= 0);
}
/*
 * NXP code end
 */

/*
 * My own code
 *
 * @brief Filling the array to send data to the client
 *
 * @param label Object name
 * @param value Accuracy
 * @param width X coordinate
 * @param height Y coordinate
 */
void fill_result_array(const char* label, float value, uint32_t width, uint32_t height){

	enum Item item = BACKGROUND;
	if (!strcmp(label, "Blue circle"))
		item = BLUE_CIRCLE;
	else if (!strcmp(label, "Blue square"))
		item = BLUE_SQUARE;
	else if (!strcmp(label, "Blue star"))
		item = BLUE_STAR;

	else if (!strcmp(label, "Green circle"))
		item = GREEN_CIRCLE;
	else if (!strcmp(label, "Green square"))
		item = GREEN_SQUARE;
	else if (!strcmp(label, "Green star"))
		item = GREEN_STAR;

	else if (!strcmp(label, "Orange circle"))
		item = ORANGE_CIRCLE;
	else if (!strcmp(label, "Orange square"))
		item = ORANGE_SQUARE;
	else if (!strcmp(label, "Orange star"))
		item = ORANGE_STAR;

	int index = 0;

	if ((width < 24) && (height < 24))
		index = 0;
	else if ((width >= 24) && (width < 48) && (height < 24))
		index = 1;
	else if ((width >= 48) && (width < 72) && (height < 24))
		index = 2;
	else if ((width >= 72) && (height < 24))
		index = 3;

	else if ((width < 24) && (height >= 24) && (height < 48))
		index = 4;
	else if ((width >= 24) && (width < 48) && (height >= 24) && (height < 48))
		index = 5;
	else if ((width >= 48) && (width < 72) && (height >= 24) && (height < 48))
		index = 6;
	else if ((width >= 72) && (height >= 24) && (height < 48))
		index = 7;

	else if ((width < 24) && (height >= 48) && (height < 72))
		index = 8;
	else if ((width >= 24) && (width < 48) && (height >= 48) && (height < 72))
		index = 9;
	else if ((width >= 48) && (width < 72) && (height >= 48) && (height < 72))
		index = 10;
	else if ((width >= 72) && (height >= 48) && (height < 72))
		index = 11;

	else if ((width < 24) && (height >= 72))
		index = 12;
	else if ((width >= 24) && (width < 48) && (height >= 72))
		index = 13;
	else if ((width >= 48) && (width < 72) && (height >= 72))
		index = 14;
	else if ((width >= 72) && (height >= 72))
		index = 15;


	index *= 4;
	if (result_array[index+1] < int(value * 100)){
		result_array[index] = item;
		result_array[index+1] = int(value * 100);
		result_array[index+2] = width;
		result_array[index+3] = height;
	}
}
/*
 * Own code end
 */


/*
 * My own code start
 *
 * @brief main operating cycle (Reading the picture, processing, sending the result)
 */
static void tcpsrv_thread(void *arg)
{
	struct netconn *conn, *newconn;
	struct netbuf *buf_write = NULL;
	err_t err;
	LWIP_UNUSED_ARG(arg);

	// TCP socket create
	conn = netconn_new(NETCONN_TCP);
	netconn_bind(conn, IP_ADDR_ANY, SERVER_PORT);
	LWIP_ERROR("tcp server: invalid conn", (conn != NULL), return;);

	netconn_listen(conn);

	PRINTF("Waiting for a new connection at port: %d\n\r", SERVER_PORT);
	err = netconn_accept(conn, &newconn);
	LWIP_ERROR("tcp server: accept failed\n\r", err == ERR_OK, lwip_strerr(err));
	PRINTF("Accepted a new connection!\n\r");
	netconn_set_recvtimeout(newconn, RECV_TIMEOUT_MS);

	buf_write = netbuf_new();

	// FOMO model initialization
	if (MODEL_Init() != kStatus_Success)
	{
		PRINTF("Failed initializing model" EOL);
		for (;;) {}
	}

	// Function for getting a picture from the camera

	// is called before the main operation cycle,
	// because the first time this function is run,
	// the camera gets a blank (black) picture
	if (IMAGE_GetImage(output) != kStatus_Success)
	{
		PRINTF("Failed retrieving input image" EOL);
		for (;;) {}
	}

	while (1) {

		if (IMAGE_GetImage(output) != kStatus_Success)
		{
			PRINTF("Failed retrieving input image" EOL);
			for (;;) {}
		}

		ei_impulse_result_t result; // Used to store inference output
		signal_t signal;            // Wrapper for raw input buffer

		// Calculate the length of the buffer
		size_t buf_len = sizeof(output) / sizeof(output[0]);

		// Make sure that the length of the buffer matches expected input length
		if (buf_len != EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE) {
			PRINTF("ERROR: The size of the input buffer is not correct.\r\n");
			PRINTF("Expected %d items, but got %d\r\n",
					EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE,
					(int)buf_len);
			return;
		}

		// Assign callback function to fill buffer used for preprocessing/inference
		signal.total_length = EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE;
		signal.get_data = &get_signal_data;

		int res;
		// Sending images for model processing and receiving the result
		res = MODEL_RunInference(&signal, &result);

		memset(result_array, 0, 64*sizeof(uint8_t));
		PRINTF("Object detection bounding boxes:\r\n");

		uint32_t max = result.bounding_boxes_count > 16 ? result.bounding_boxes_count : 16;

		// result structure filling
		for (uint32_t i = 0; i < max; i++) {
			ei_impulse_result_bounding_box_t bb = result.bounding_boxes[i];
			if (bb.value == 0) {
				continue;
			}

			fill_result_array(bb.label, bb.value, bb.x, bb.y);
 			PRINTF("  %s \r\n",
					bb.label);
		}

		struct netbuf *buf_read;
		void *data;
		u16_t len;

		// Sending data to the client
		err = netconn_recv(newconn, &buf_read);

		if (err == ERR_OK)
		{
			netbuf_data(buf_read, &data, &len);

			if ((len == 1) && (!(strncmp((char*)data,"C", len))))
			{
				PRINTF("Received the command to close the connection!\n\r");

				tcpsrv_sendMessage(buf_write, newconn, ack, ACK_LENGTH);

				netbuf_delete(buf_read);
				netconn_close(newconn);
				netconn_delete(newconn);

				PRINTF("Waiting for a new connection at port: %d\n\r", SERVER_PORT);
				err = netconn_accept(conn, &newconn);
				LWIP_ERROR("tcp server: accept failed\n\r", err == ERR_OK, lwip_strerr(err));

				PRINTF("Accepted a new connection!\n\r");
				netconn_set_recvtimeout(newconn, RECV_TIMEOUT_MS);
				continue;
			}
			else
			{
				PRINTF("Received the following message: %s\n\r", data);
				netbuf_delete(buf_read);
			}
		}

		tcpsrv_sendMessage(buf_write, newconn, "send", MESSAGE_LENGTH);
	}
}


void tcpsrv_init(void)
{
	sys_thread_new("tcpsrv_thread", tcpsrv_thread, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
}
/*-----------------------------------------------------------------------------------*/

#endif /* LWIP_NETCONN */
