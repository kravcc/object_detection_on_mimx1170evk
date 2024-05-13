// This file is a combination of my code and the code from the sources

/*
 * Autor: Marina Kravchuk
 */

/*
 * Copyright (c) 2022 EdgeImpulse Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "demo_config.h"
#include "fsl_debug_console.h"
#include "image.h"
#include "image_utils.h"
#include "image_data.h"
#include "eiq_video_worker.h"
#include "model.h"
//#include "task.h"
//#include "FreeRTOS.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Pointer to video worker. */
static EIQ_VideoWorker_t* s_worker = NULL;
/* Pointer to capture buffer. */
static uint8_t* s_captureBuffer = NULL;
/* Dimensions of capture buffer. */
static Dims_t s_captureBufferDims;

constexpr int R_OFFSET = 0, G_OFFSET = 1, B_OFFSET = 2;
uint8_t image_rgb888_packed[FRAME_BUFFER_COLS * FRAME_BUFFER_ROWS * 3] = {0};

/*******************************************************************************
 * Code
 ******************************************************************************/

/** Edge Impulse code
 * @brief Callback: fill a section of the out_ptr buffer when requested
 */
int image_get_data(size_t offset, size_t length, float *out_ptr) {
    uint32_t out_ptr_ix = 0;

    //change offset from float pointer (size 4) to packed RGB (1B ptr)
    offset = offset*3;

    while (length != 0) {
        // clang-format off
        out_ptr[out_ptr_ix] =
            (image_rgb888_packed[offset + R_OFFSET] << 16) +
            (image_rgb888_packed[offset + G_OFFSET] << 8) +
            image_rgb888_packed[offset + B_OFFSET];
        // clang-format on

        // and go to the next pixel
        out_ptr_ix++;
        offset+=3;
        length--;
    }

    // and done!
    return 0;
}


/** Edge Impulse code
 * @brief Resize an image using interpolation
 * Can be used to resize the image smaller or larger
 * If resizing much smaller than 1/3 size, then a more rubust algorithm should average all of the pixels
 * This algorithm uses bilinear interpolation - averages a 2x2 region to generate each new pixel
 *
 * @param srcWidth Input image width in pixels
 * @param srcHeight Input image height in pixels
 * @param srcImage Input buffer
 * @param dstWidth Output image width in pixels
 * @param dstHeight Output image height in pixels
 * @param dstImage Output buffer, can be same as input buffer
 * @param pixel_size_B Size of pixels in Bytes.  3 for RGB, 1 for mono
 */
int resize_image(
    const uint8_t *srcImage,
    int srcWidth,
    int srcHeight,
    uint8_t *dstImage,
    int dstWidth,
    int dstHeight,
    int pixel_size_B)
{
// Copied from ei_camera.cpp in firmware-eta-compute
// Modified for RGB888
// This needs to be < 16 or it won't fit. Cortex-M4 only has SIMD for signed multiplies
    constexpr int FRAC_BITS = 14;
    constexpr int FRAC_VAL = (1 << FRAC_BITS);
    constexpr int FRAC_MASK = (FRAC_VAL - 1);

    uint32_t src_x_accum, src_y_accum; // accumulators and fractions for scaling the image
    uint32_t x_frac, nx_frac, y_frac, ny_frac;
    int x, y, ty;

    if (srcHeight < 2) {
        return kStatus_Fail;
    }

    // start at 1/2 pixel in to account for integer downsampling which might miss pixels
    src_y_accum = FRAC_VAL / 2;
    const uint32_t src_x_frac = (srcWidth * FRAC_VAL) / dstWidth;
    const uint32_t src_y_frac = (srcHeight * FRAC_VAL) / dstHeight;

    //from here out, *3 b/c RGB
    srcWidth *= pixel_size_B;
    //srcHeight not used for indexing
    //dstWidth still needed as is
    //dstHeight shouldn't be scaled

    const uint8_t *s;
    uint8_t *d;

    for (y = 0; y < dstHeight; y++) {
        // do indexing computations
        ty = src_y_accum >> FRAC_BITS; // src y
        y_frac = src_y_accum & FRAC_MASK;
        src_y_accum += src_y_frac;
        ny_frac = FRAC_VAL - y_frac; // y fraction and 1.0 - y fraction

        s = &srcImage[ty * srcWidth];
        d = &dstImage[y * dstWidth * pixel_size_B]; //not scaled above
        // start at 1/2 pixel in to account for integer downsampling which might miss pixels
        src_x_accum = FRAC_VAL / 2;
        for (x = 0; x < dstWidth; x++) {
            uint32_t tx, p00, p01, p10, p11;
            // do indexing computations
            tx = (src_x_accum >> FRAC_BITS) * pixel_size_B;
            x_frac = src_x_accum & FRAC_MASK;
            nx_frac = FRAC_VAL - x_frac; // x fraction and 1.0 - x fraction
            src_x_accum += src_x_frac;

            //interpolate and write out
            for (int color = 0; color < pixel_size_B;
                 color++) // do pixel_size_B times for pixel_size_B colors
            {
                p00 = s[tx];
                p10 = s[tx + pixel_size_B];
                p01 = s[tx + srcWidth];
                p11 = s[tx + srcWidth + pixel_size_B];
                p00 = ((p00 * nx_frac) + (p10 * x_frac) + FRAC_VAL / 2) >> FRAC_BITS; // top line
                p01 = ((p01 * nx_frac) + (p11 * x_frac) + FRAC_VAL / 2) >> FRAC_BITS; // bottom line
                p00 = ((p00 * ny_frac) + (p01 * y_frac) + FRAC_VAL / 2) >> FRAC_BITS; //top + bottom
                *d++ = (uint8_t)p00; // store new pixel
                //ready next loop
                tx++;
            }
        } // for x
    } // for y
    return kStatus_Success;
}
/*
 * Edge Impulse code end
 */


/*
 * Edge Impulse code
 * @brief Crops an image. Can be in-place. 4B alignment for best performance
 * (Alignment is tested, will fall back to B by B movement)
 *
 * @param srcWidth X dimension in pixels
 * @param srcHeight Y dimension in pixels
 * @param srcImage Input buffer
 * @param startX X coord of first pixel to keep
 * @param startY Y coord of the first pixel to keep
 * @param dstWidth Desired X dimension in pixels (should be smaller than srcWidth)
 * @param dstHeight Desired Y dimension in pixels (should be smaller than srcHeight)
 * @param dstImage Output buffer, can be the same as srcImage
 * @param iBpp 8 or 16 for bits per pixel
 */
int cropImage(
    const uint8_t *srcImage,
    int srcWidth,
    int srcHeight,
    int startX,
    int startY,
    uint8_t *dstImage,
    int dstWidth,
    int dstHeight,
    int iBpp)
{
    uint32_t *s32, *d32;
    int x, y;

    if (startX < 0 || startX >= srcWidth || startY < 0 || startY >= srcHeight ||
        (startX + dstWidth) > srcWidth || (startY + dstHeight) > srcHeight) {
        return kStatus_Fail; // invalid parameters
    }
    if (iBpp != 8 && iBpp != 16) {
        return kStatus_Fail;
    }

    if (iBpp == 8) {
        const uint8_t *s;
        uint8_t *d;
        for (y = 0; y < dstHeight; y++) {
            s = &srcImage[srcWidth * (y + startY) + startX];
            d = &dstImage[(dstWidth * y)];
            x = 0;
            if ((intptr_t)s & 3 || (intptr_t)d & 3) { // either src or dst pointer is not aligned
                for (; x < dstWidth; x++) {
                    *d++ = *s++; // have to do it byte-by-byte
                }
            }
            else {
                // move 4 bytes at a time if aligned or alignment not enforced
                s32 = (uint32_t *)s;
                d32 = (uint32_t *)d;
                for (; x < dstWidth - 3; x += 4) {
                    *d32++ = *s32++;
                }
                // any remaining stragglers?
                s = (uint8_t *)s32;
                d = (uint8_t *)d32;
                for (; x < dstWidth; x++) {
                    *d++ = *s++;
                }
            }
        } // for y
    } // 8-bpp
    else {
        uint16_t *s, *d;
        for (y = 0; y < dstHeight; y++) {
            s = (uint16_t *)&srcImage[2 * srcWidth * (y + startY) + startX * 2];
            d = (uint16_t *)&dstImage[(dstWidth * y * 2)];
            x = 0;
            if ((intptr_t)s & 2 || (intptr_t)d & 2) { // either src or dst pointer is not aligned
                for (; x < dstWidth; x++) {
                    *d++ = *s++; // have to do it 16-bits at a time
                }
            }
            else {
                // move 4 bytes at a time if aligned or alignment no enforced
                s32 = (uint32_t *)s;
                d32 = (uint32_t *)d;
                for (; x < dstWidth - 1; x += 2) { // we can move 2 pixels at a time
                    *d32++ = *s32++;
                }
                // any remaining stragglers?
                s = (uint16_t *)s32;
                d = (uint16_t *)d32;
                for (; x < dstWidth; x++) {
                    *d++ = *s++;
                }
            }
        } // for y
    } // 16-bpp case

    return kStatus_Success;
} /* cropImage() */



/*
 * Edge Impulse code
 * @brief transfer function
 *
 * @param srcImage Pointer to source image
 * @param srcWidth Input width in pixels
 * @param srcHeight Input height in pixels
 * @param startX X coord of first pixel to keep
 * @param startY Y coord of first pixel to keep
 * @param dstImage Pointer to destination image
 * @param dstWidth Ultimate width in pixels
 * @param dstHeight Ultimate height in pixels
 */
int crop_image_rgb888_packed(
    const uint8_t *srcImage,
    int srcWidth,
    int srcHeight,
    int startX,
    int startY,
    uint8_t *dstImage,
    int dstWidth,
    int dstHeight)
{
    // use 8 bpp mode, but do everything *3 for RGB
    return cropImage(
        srcImage,
        srcWidth * 3,
        srcHeight,
        startX * 3,
        startY,
        dstImage,
        dstWidth * 3,
        dstHeight,
        8);
}


/*
 * Edge Impulse code
 * @brief Calculate new dims that match the aspect ratio of destination
 * This prevents a squashed look
 * The smallest axis is held constant
 *
 * @param srcWidth Input width in pixels
 * @param srcHeight Input height in pixels
 * @param dstWidth Ultimate width in pixels
 * @param dstHeight Ultimate height in pixels
 * @param[out] cropWidth Width in pixels that matches the aspect ratio
 * @param[out] cropHeight Height in pixels that matches the aspect ratio
 */
void calculate_crop_dims(
    int srcWidth,
    int srcHeight,
    int dstWidth,
    int dstHeight,
    int &cropWidth,
    int &cropHeight)
{
    //first, trim the largest axis to match destination aspect ratio
    //calculate by fixing the smaller axis
    if (srcWidth > srcHeight) {
        cropWidth = (uint32_t)(dstWidth * srcHeight) / dstHeight; //cast in case int is small
        cropHeight = srcHeight;
    }
    else {
        cropHeight = (uint32_t)(dstHeight * srcWidth) / dstWidth;
        cropWidth = srcWidth;
    }
}


/*
 * Edge Impulse code
 * @brief function set for cropping and normalization
 *
 * @param srcImage Pointer to source image
 * @param srcWidth Input width in pixels
 * @param srcHeight Input height in pixels
 * @param dstImage Pointer to destination image
 * @param dstWidth Ultimate width in pixels
 * @param dstHeight Ultimate height in pixels
 */
int crop_and_interpolate_rgb888(
    const uint8_t *srcImage,
    int srcWidth,
    int srcHeight,
    uint8_t *dstImage,
    int dstWidth,
    int dstHeight)
{
    int cropWidth, cropHeight;
    // What are dimensions that maintain aspect ratio?
    calculate_crop_dims(srcWidth, srcHeight, dstWidth, dstHeight, cropWidth, cropHeight);
    // Now crop to that dimension
    int res = crop_image_rgb888_packed(
        srcImage,
        srcWidth,
        srcHeight,
        (srcWidth - cropWidth) / 2,
        (srcHeight - cropHeight) / 2,
        dstImage,
        cropWidth,
        cropHeight);

    if( res != kStatus_Success) { return res; }
    // Finally, interpolate down to desired dimensions, in place
    return resize_image(dstImage, cropWidth, cropHeight, dstImage, dstWidth, dstHeight, 3);
}
/*
 * Edge Impulse code end
 */




/*! My own code
 * @brief Stores image data to destination buffer.
 *
 * This function gets image from static image or from camera device.
 *
 * @param output address of destination buffer for storing image data
 * @return status code
 */
status_t IMAGE_GetImage(float* output)
{

	if (s_worker == NULL)
	{
		PRINTF(EOL "Camera data processing:" EOL);
		s_worker = EIQ_InitVideoWorker();
		s_captureBuffer = s_worker->base.getData();
		s_captureBufferDims = s_worker->base.getResolution();
		s_worker->base.start();
	}

	while (!s_worker->base.isReady()) {}
	PRINTF(EOL "Data for inference are ready" EOL);

	crop_and_interpolate_rgb888(s_captureBuffer, // const uint8_t *srcImage,
								FRAME_BUFFER_COLS, // int srcWidth,
								FRAME_BUFFER_ROWS, //int srcHeight,
								image_rgb888_packed, // uint8_t *dstImage,
								EI_CLASSIFIER_INPUT_WIDTH, // int dstWidth,
								EI_CLASSIFIER_INPUT_HEIGHT); // int dstHeight);
	signal_t signal;
	signal.total_length = EI_CLASSIFIER_INPUT_WIDTH * EI_CLASSIFIER_INPUT_HEIGHT;
	signal.get_data = &image_get_data;

	for (size_t ix = 0; ix < signal.total_length; ix += 1024) {
		size_t bytes_to_read = 1024;
		if (ix + bytes_to_read > signal.total_length) {
			bytes_to_read = signal.total_length - ix;
		}

		int r = signal.get_data(ix, bytes_to_read, output + ix);
		if (r != 0) {
			return kStatus_Fail;
		}
	}

    return kStatus_Success;
}

