/* SPDX-License-Identifier:BSD-3-Clause */
#ifndef VK_H
#define VK_H

#include <vulkan/vulkan.h>
#include "../../types.h"
#include "../../rgfw.h"

struct queue_family_indices {
	u32 graphics, present;
};

struct renderer_context {
	VkInstance instance;
	VkPhysicalDevice physical_device;
	VkDevice device;
	VkQueue graphics_queue, present_queue;
	VkSurfaceKHR surface;
	struct queue_family_indices queue_indices;
	RGFW_window *window;
};

#endif
