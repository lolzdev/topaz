/* SPDX-License-Identifier:BSD-3-Clause */
#ifndef PHYSICAL_DEVICE_H
#define PHYSICAL_DEVICE_H

#include "vk.h"
#include "../../types.h"
#include "../../core/vector.h"


/*
 * Get the list of all available devices and pick the best option.
 */
void vk_physical_device_pick(struct renderer_context *context);
/*
 * Get the list of all available device extensions and return a vector
 * containing those.
 */
struct vector *vk_physical_device_get_extensions(struct renderer_context *context);
/*
 * The physical device is responsible of selecting the queue family indices,
 * used later by the device to create the queues. This function sets the family
 * indices in the renderer context.
 */
void vk_physical_device_select_family_indices(struct renderer_context *context);

#endif
