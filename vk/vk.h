/* SPDX-License-Identifier:BSD-3-Clause */
#ifndef VK_H
#define VK_H

#include <vulkan/vulkan.h>
#include "../types.h"

struct queue_family_indices {
	u32 graphics, present;
};

struct renderer_context {
	VkInstance instance;
	VkPhysicalDevice physical_device;
	VkDevice device;
	VkQueue graphics_queue;
	struct queue_family_indices queue_indices;
};

#endif
