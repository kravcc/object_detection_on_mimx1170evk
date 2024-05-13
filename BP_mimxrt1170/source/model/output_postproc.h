/*
 * functions and structures are taken from EdgeImpulse
 * Copyright (c) 2022 EdgeImpulse Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#ifndef _OUTPUT_POSTPROCESS_H_
#define _OUTPUT_POSTPROCESS_H_

#include "model.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef struct cube {
    size_t x;
    size_t y;
    size_t width;
    size_t height;
    float confidence;
    const char *label;
} ei_classifier_cube_t;


int fill_result_struct_from_output_tensor_tflite(ei_impulse_result_t *result,
								int8_t *data,
								float zero_point,
								float scale,
								int out_width,
								int out_height);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

#endif /* _OUTPUT_POSTPROCESS_H_ */
