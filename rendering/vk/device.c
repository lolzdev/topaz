/* SPDX-License-Identifier:BSD-3-Clause */
#include "device.h"
#include "physical_device.h"
#include "../../core/vector.h"
#include "../../core/log.h"

#include <string.h>

void vk_device_init(struct renderer_context *context)
{
	struct vector *device_extensions = vector_init(0, sizeof(char *));
	struct vector *physical_device_extensions = vk_physical_device_get_extensions(context);
	for (usize i = 0; i < physical_device_extensions->length; i++) {
		if (strcmp(((char **)physical_device_extensions->data)[i], "VK_KHR_portability_subset") == 0) {
			/*
			 * The spec states that if VK_KHR_portability_subset is
			 * present in the physical device extensions, the
			 * device should also have that extension enabled.
			 */
			vector_push(device_extensions, char *, "VK_KHR_portability_subset");
		}

		free(((char **)physical_device_extensions->data)[i]);
	}

	f32 priority = 0.0;
	VkDeviceQueueCreateInfo graphics_queue_create_info[2];
	graphics_queue_create_info[0] = (VkDeviceQueueCreateInfo){
		.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		.queueFamilyIndex = context->queue_indices.graphics,
		.queueCount = 1,
		.pQueuePriorities = &priority
	};

	graphics_queue_create_info[1] = (VkDeviceQueueCreateInfo){
		.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		.queueFamilyIndex = context->queue_indices.present,
		.queueCount = 1,
		.pQueuePriorities = &priority
	};

	VkDeviceCreateInfo device_create_info = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.queueCreateInfoCount = 2,
		.pQueueCreateInfos = graphics_queue_create_info,
		.enabledLayerCount = 0,
		.ppEnabledLayerNames = NULL,
		.enabledExtensionCount = device_extensions->length,
		.ppEnabledExtensionNames = (const char **)device_extensions->data,
		.pEnabledFeatures = NULL,
	};

	if (vkCreateDevice(context->physical_device, &device_create_info, NULL, &context->device) != VK_SUCCESS) {
		vector_deinit(physical_device_extensions);
		vector_deinit(device_extensions);
		fatal("Can't create Vulkan device.\n");
	}

	vkGetDeviceQueue(context->device, graphics_queue_create_info[0].queueFamilyIndex, 0, &context->graphics_queue);
	vkGetDeviceQueue(context->device, graphics_queue_create_info[1].queueFamilyIndex, 0, &context->present_queue);

	vector_deinit(physical_device_extensions);
	vector_deinit(device_extensions);
}

void vk_device_deinit(struct renderer_context *context)
{
	vkDestroyDevice(context->device, NULL);
}
