/*
 * Functions and structures are taken from EdgeImpulse
 *
 * Copyright (c) 2022 EdgeImpulse Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _MODEL_H_
#define _MODEL_H_

#include <stdint.h>
#include <functional>

#include "fsl_common.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define MAX_TENSOR_DIMS 4
#define EI_CLASSIFIER_RAW_SAMPLE_COUNT              9216
#define EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME         1
#define EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE          (EI_CLASSIFIER_RAW_SAMPLE_COUNT * EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME)
#define EI_CLASSIFIER_MAX_OBJECT_DETECTION_COUNT    16 //??
#define EI_CLASSIFIER_MAX_LABELS_COUNT              25  // ??

typedef struct {
    const char *label;
    float value;
} ei_impulse_result_classification_t;

typedef struct {
    const char *label;
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
    float value;
} ei_impulse_result_bounding_box_t;

typedef struct {
    int sampling;
    int dsp;
    int classification;
    int anomaly;
    int64_t dsp_us;
    int64_t classification_us;
    int64_t anomaly_us;
} ei_impulse_result_timing_t;

typedef struct {
    ei_impulse_result_bounding_box_t *bounding_boxes;
    uint32_t bounding_boxes_count;
    ei_impulse_result_classification_t classification[EI_CLASSIFIER_MAX_LABELS_COUNT];
    float anomaly;
    ei_impulse_result_timing_t timing;
} ei_impulse_result_t;

/**
 * Sensor signal structure
 */
typedef struct ei_signal_t {
    /**
     * A function to retrieve part of the sensor signal
     * No bytes will be requested outside of the `total_length`.
     * @param offset The offset in the signal
     * @param length The total length of the signal
     * @param out_ptr An out buffer to set the signal data
     */
    std::function<int(size_t offset, size_t length, float *out_ptr)> get_data;
    size_t total_length;
} signal_t;



typedef struct
{
  int32_t zero_point;
  float scale;
} tensor_quant_t;

typedef struct
{
  uint32_t size;
  uint32_t data[MAX_TENSOR_DIMS];
} tensor_dims_t;

typedef enum
{
    kTensorType_FLOAT32 = 0,
    kTensorType_UINT8 = 1,
    kTensorType_INT8 = 2
} tensor_type_t;

status_t MODEL_Init(void);
status_t MODEL_RunInference(signal_t* signal, ei_impulse_result_t* result);


#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _MODEL_H_ */
