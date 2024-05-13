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


#include "tensorflow/lite/micro/kernels/micro_ops.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_op_resolver.h"
#include "tensorflow/lite/schema/schema_generated.h"

#include "output_postproc.h"
#include "fsl_debug_console.h"
#include "model.h"
#include "model_data.h"

static const tflite::Model* s_model = nullptr;
static tflite::MicroInterpreter* s_interpreter = nullptr;

extern tflite::MicroOpResolver &MODEL_GetOpsResolver();

// An area of memory to use for input, output, and intermediate arrays.
// (Can be adjusted based on the model needs.)
static uint8_t s_tensorArena[kTensorArenaSize] __ALIGNED(16);


/*
 * Edge Impulse code
 * @brief Normalization
 */
int extract_image_features_quantized(signal_t *signal, int8_t *output_matrix, float scale,
									float zero_point) {
	//int16_t channel_count = 3;
	size_t output_ix = 0;

//	const int32_t iRedToGray = (int32_t)(0.299f * 65536.0f);
//	const int32_t iGreenToGray = (int32_t)(0.587f * 65536.0f);
//	const int32_t iBlueToGray = (int32_t)(0.114f * 65536.0f);
//
//	static const float torch_mean[] = { 0.485, 0.456, 0.406 };
//	static const float torch_std[] = { 0.229, 0.224, 0.225 };

	const size_t page_size = 1024;// here

	size_t bytes_left = signal->total_length;
	    for (size_t ix = 0; ix < signal->total_length; ix += page_size) {
	        size_t elements_to_read = bytes_left > page_size ? page_size : bytes_left;

	        float input_matrix[elements_to_read * sizeof(float)];
	        signal->get_data(ix, elements_to_read, input_matrix);

	        for (size_t jx = 0; jx < elements_to_read; jx++) {
	                    uint32_t pixel = static_cast<uint32_t>(input_matrix[jx]);

	                    int32_t r = static_cast<int32_t>(pixel >> 16 & 0xff);
						int32_t g = static_cast<int32_t>(pixel >> 8 & 0xff);
						int32_t b = static_cast<int32_t>(pixel & 0xff);

						output_matrix[output_ix++] = static_cast<int8_t>(r + zero_point);
						output_matrix[output_ix++] = static_cast<int8_t>(g + zero_point);
						output_matrix[output_ix++] = static_cast<int8_t>(b + zero_point);
	        }

	    bytes_left -= elements_to_read;
	    }
	return kStatus_Success;
}


/*
 * NXP code
 * @brief Model initialization
 */

status_t MODEL_Init(void)
{
    // Map the model into a usable data structure. This doesn't involve any
    // copying or parsing, it's a very lightweight operation.
    s_model = tflite::GetModel(model_data);
    if (s_model->version() != TFLITE_SCHEMA_VERSION)
    {
        PRINTF("Model provided is schema version %d not equal "
               "to supported version %d.",
               s_model->version(), TFLITE_SCHEMA_VERSION);
        return kStatus_Fail;
    }

    // Pull in only the operation implementations we need.
    // This relies on a complete list of all the ops needed by this graph.
    // An easier approach is to just use the AllOpsResolver, but this will
    // incur some penalty in code space for op implementations that are not
    // needed by this graph.
    //
    // tflite::AllOpsResolver resolver;
    // NOLINTNEXTLINE(runtime-global-variables)
    tflite::MicroOpResolver &micro_op_resolver = MODEL_GetOpsResolver();

    // Build an interpreter to run the model with.
    static tflite::MicroInterpreter static_interpreter(
        s_model, micro_op_resolver, s_tensorArena, kTensorArenaSize);
    s_interpreter = &static_interpreter;

    // Allocate memory from the tensor_arena for the model's tensors.
    TfLiteStatus allocate_status = s_interpreter->AllocateTensors();
    if (allocate_status != kTfLiteOk)
    {
        PRINTF("AllocateTensors() failed");
        return kStatus_Fail;
    }

    return kStatus_Success;
}
/*
 * NXP code end
 */


/*
 * My own code
 * @brief model run
 *
 * @param signal input structure
 * @param result Output structure
 */
status_t MODEL_RunInference(signal_t* signal, ei_impulse_result_t* result)
{
	memset(result, 0, sizeof(ei_impulse_result_t));

	uint64_t ctx_start_us;
	TfLiteTensor* input = s_interpreter->input(0);
	TfLiteTensor* output = s_interpreter->output(0);

	int out_width_height = 12;

	//int8_t *output_matrix = {0};

	int ret = extract_image_features_quantized(signal, input->data.int8, input->params.scale, input->params.zero_point);


    if (s_interpreter->Invoke() != kTfLiteOk)
    {
        PRINTF("Invoke failed!\r\n");
        return kStatus_Fail;
    }

    int fill_res = fill_result_struct_from_output_tensor_tflite(result, output->data.int8, output->params.zero_point, output->params.scale, out_width_height, out_width_height);

    return kStatus_Success;
}
