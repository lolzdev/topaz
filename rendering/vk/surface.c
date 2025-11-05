/* SPDX-License-Identifier:BSD-3-Clause */
#include "surface.h"
#include "../../core/log.h"

/*
 * This function is defined in rgfw.h
*/
VkResult RGFW_window_createSurface_Vulkan(RGFW_window * win, VkInstance instance, VkSurfaceKHR * surface);

/*
 * RGFW exposes a platform independent function to
 * create a Vulkan surface.
*/
void vk_surface_init(struct renderer_context *context)
{
	if (RGFW_window_createSurface_Vulkan(context->window, context->instance, &context->surface) != VK_SUCCESS) {
		fatal("Can't create Vulkan surface.\n");
	}
}

void vk_surface_deinit(struct renderer_context *context)
{
	vkDestroySurfaceKHR(context->instance, context->surface, NULL);
}
