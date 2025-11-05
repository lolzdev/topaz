/* SPDX-License-Identifier:BSD-3-Clause */
#include "physical_device.h"
#include "../../core/log.h"
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
	/* 
	 * Use 0xaa as a known value to specify that these
	 * indices have not been found yet.
	 */
	context->queue_indices.graphics = 0xaa;
	context->queue_indices.present = 0xaa;
	/*
	 * This loop iterates over all the family properties
	 * provided by the physical device and searches for
	 * two unique queue family indices, one for presentation
	 * and one for graphics.
	 */
	for (u32 i = 0; i < property_count; i++) {
		if (context->queue_indices.graphics != 0xaa && context->queue_indices.present != 0xaa) break;
		VkQueueFamilyProperties prop = properties[i];

		if ((prop.queueFlags & VK_QUEUE_GRAPHICS_BIT) && context->queue_indices.graphics == 0xaa) {
			context->queue_indices.graphics = i;
			continue;
		}

		VkBool32 present_support = VK_FALSE;
		if (vkGetPhysicalDeviceSurfaceSupportKHR(context->physical_device, i, context->surface, &present_support) != VK_SUCCESS) {
			free(properties);
			fatal("Can't check for surface support.\n");
		}

		if (present_support == VK_TRUE) context->queue_indices.present = i;
	}

	free(properties);
}
