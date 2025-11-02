#ifndef VK_H
#define VK_H

#include <vulkan/vulkan.h>
struct renderer_context {
	VkInstance instance;
	VkPhysicalDevice physical_device;
};

#endif
