// SPDX-License-Identifier: BSD-3-Clause
#include "physical_device.h"
#include "../core/log.h"
#include <stdio.h>
#include <string.h>

void vk_physical_device_pick(struct renderer_context *context)
{
	u32 device_count = 0;

	vkEnumeratePhysicalDevices(context->instance, &device_count, NULL);

	VkPhysicalDevice *devices = malloc(sizeof(VkPhysicalDevice) * device_count);

	if (vkEnumeratePhysicalDevices(context->instance, &device_count, devices) != VK_SUCCESS || device_count == 0) {
		fatal("Can't get physical devices.\n");
	}

	log_info("Available devices:\n");
	for (usize i = 0; i < device_count; i++) {
		VkPhysicalDeviceProperties properties;
		vkGetPhysicalDeviceProperties(devices[i], &properties);
		printf("%s\n", properties.deviceName);
	}

	context->physical_device = devices[0];

	free(devices);
}

struct vector *vk_physical_device_get_extensions(struct renderer_context *context)
{
	u32 property_count = 0;
	VkExtensionProperties *properties = NULL;

	vkEnumerateDeviceExtensionProperties(context->physical_device, NULL, &property_count, NULL);
	
	struct vector *extensions = vector_init(property_count, sizeof(char *));
	properties = (VkExtensionProperties *) malloc(sizeof(VkExtensionProperties) * property_count);

	if (vkEnumerateDeviceExtensionProperties(context->physical_device, NULL, &property_count, properties) != VK_SUCCESS) {
		free(properties);
		fatal("Can't get physical device extension properties.\n");
	}

	for (usize i = 0; i < property_count; i++) {
		char *name = malloc(strlen(properties[i].extensionName) + 1);
		strcpy(name, properties[i].extensionName);
		vector_push(extensions, char *, name);
	}

	free(properties);
	
	return extensions;
}

void vk_physical_device_select_family_indices(struct renderer_context *context)
{
	u32 property_count = 0;
	VkQueueFamilyProperties *properties = NULL;

	vkGetPhysicalDeviceQueueFamilyProperties(context->physical_device, &property_count, NULL);

	properties = (VkQueueFamilyProperties *) malloc(sizeof(VkExtensionProperties) * property_count);

	vkGetPhysicalDeviceQueueFamilyProperties(context->physical_device, &property_count, properties);

	for (u32 i = 0; i < property_count; i++) {
		VkQueueFamilyProperties prop = properties[i];

		if (prop.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			context->queue_indices.graphics = i;
		}
	}

	free(properties);
}
