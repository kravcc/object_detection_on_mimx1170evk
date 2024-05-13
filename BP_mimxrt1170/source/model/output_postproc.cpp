/*
 *
 * Copyright (c) 2022 EdgeImpulse Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <iostream>
#include <algorithm>
#include <vector>

#include "fsl_debug_console.h"
#include "output_postproc.h"
#include "demo_config.h"
#include "labels.h"
#ifdef EIQ_GUI_PRINTF
#include "chgui.h"
#endif


/**
 * @brief Checks whether a new section overlaps with a cube,
 * 		  and if so, will **update the cube**
 * @param c cube structure
 * @param x X coord of the object
 * @param y Y coord of the object
 * @param width Object width
 * @param height Object height
 * @param confidence Probability of prediction
 */
static bool ei_cube_check_overlap(ei_classifier_cube_t *c, int x, int y, int width, int height, float confidence) {
    bool is_overlapping = !(c->x + c->width < x || c->y + c->height < y || c->x > x + width || c->y > y + height);
    if (!is_overlapping) return false;

    // if we overlap, but the x of the new box is lower than the x of the current box
    if (x < c->x) {
        // update x to match new box and make width larger (by the diff between the boxes)
        c->x = x;
        c->width += c->x - x;
    }
    // if we overlap, but the y of the new box is lower than the y of the current box
    if (y < c->y) {
        // update y to match new box and make height larger (by the diff between the boxes)
        c->y = y;
        c->height += c->y - y;
    }
    // if we overlap, and x+width of the new box is higher than the x+width of the current box
    if (x + width > c->x + c->width) {
        // just make the box wider
        c->width += (x + width) - (c->x + c->width);
    }
    // if we overlap, and y+height of the new box is higher than the y+height of the current box
    if (y + height > c->y + c->height) {
        // just make the box higher
        c->height += (y + height) - (c->y + c->height);
    }
    // if the new box has higher confidence, then override confidence of the whole box
    if (confidence > c->confidence) {
        c->confidence = confidence;
    }
    return true;
}


/*
 * @brief Callback: fill the ei_impulse_result_t structure
 * @param result Result structure
 * @param cubes Vector of the cubes structures
 * @param out_width_factor
 * @param object_detection_count Objects count
 */
static void fill_result_struct_from_cubes(ei_impulse_result_t *result, std::vector<ei_classifier_cube_t*> *cubes, int out_width_factor, uint32_t object_detection_count) {
    std::vector<ei_classifier_cube_t*> bbs;
    static std::vector<ei_impulse_result_bounding_box_t> results;
    int added_boxes_count = 0;
    results.clear();
    for (auto sc : *cubes) {
        bool has_overlapping = false;

        int x = sc->x;
        int y = sc->y;
        int width = sc->width;
        int height = sc->height;
        const char *label = sc->label;
        float vf = sc->confidence;

        for (auto c : bbs) {
            // not cube for same class? continue
            if (strcmp(c->label, label) != 0) continue;

            if (ei_cube_check_overlap(c, x, y, width, height, vf)) {
                has_overlapping = true;
                break;
            }
        }

        if (has_overlapping) {
            continue;
        }

        bbs.push_back(sc);

        ei_impulse_result_bounding_box_t tmp = {
            .label = sc->label,
            .x = (uint32_t)(sc->x * out_width_factor),
            .y = (uint32_t)(sc->y * out_width_factor),
            .width = (uint32_t)(sc->width * out_width_factor),
            .height = (uint32_t)(sc->height * out_width_factor),
            .value = sc->confidence
        };

        results.push_back(tmp);
        added_boxes_count++;
    }

    // if we didn't detect min required objects, fill the rest with fixed value
    if (added_boxes_count <= object_detection_count) {
        results.resize(object_detection_count);
        for (size_t ix = added_boxes_count; ix < object_detection_count; ix++) {
            results[ix].value = 0.0f;
        }
    }

    for (auto c : *cubes) {
        delete c;
    }

    result->bounding_boxes = results.data();
    result->bounding_boxes_count = results.size();
}

/*
 * @brief Screening out low-probability results
 *
 * @param cubes vector of the cubes structures
 * @param x X coord of the object
 * @param y Y coord of the object
 * @param vf Probability of prediction
 * @param label Object name
 * @param detection_threshold Minimum prediction limit
 */
static void ei_handle_cube(std::vector<ei_classifier_cube_t*> *cubes, int x, int y, float vf, const char *label, float detection_threshold) {
    if (vf < detection_threshold) return;

    bool has_overlapping = false;
    int width = 1;
    int height = 1;

    for (auto c : *cubes) {
        // not cube for same class? continue
        if (strcmp(c->label, label) != 0) continue;

        if (ei_cube_check_overlap(c, x, y, width, height, vf)) {
            has_overlapping = true;
            break;
        }
    }

    if (!has_overlapping) {
        ei_classifier_cube_t *cube = new ei_classifier_cube_t();
        cube->x = x;
        cube->y = y;
        cube->width = 1;
        cube->height = 1;
        cube->confidence = vf;
        cube->label = label;
        cubes->push_back(cube);
    }
}


/*
 * @brief Callback: fill the result structure
 */
int fill_result_struct_from_output_tensor_tflite(ei_impulse_result_t *result,
								int8_t *data,
								float zero_point,
								float scale,
								int out_width,
								int out_height) {

	std::vector<ei_classifier_cube_t*> cubes;

	int input_width = 96;
	int label_count = 9;
	int out_width_factor = input_width / out_width;
	int object_detection_count = 16;

	// out_width = out_height = 12
	for (size_t y = 0; y < out_width; y++) {
		// ei_printf("    [ ");
		for (size_t x = 0; x < out_height; x++) {
			size_t loc = ((y * out_height) + x) * (label_count + 1);

			for (size_t ix = 1; ix < label_count + 1; ix++) {
				int8_t v = data[loc+ix];
				float vf = static_cast<float>(v - zero_point) * scale;

				ei_handle_cube(&cubes, x, y, vf, labels[ix - 1], 0.5);
			}
		}
	}

	fill_result_struct_from_cubes(result, &cubes, out_width_factor, object_detection_count);

	return kStatus_Success;
}
