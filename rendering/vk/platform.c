/* SPDX-License-Identifier:BSD-3-Clause */

#define RGFW_VULKAN
#define RGFW_IMPLEMENTATION
#include <vulkan/vulkan.h>
#include "../../core/log.h"

#include "../renderer.h"

#ifdef PLATFORM_MACOS
#include <vulkan/vulkan_macos.h>
#include <vulkan/vulkan_metal.h>
void macos_set_window_layer(RGFW_window *window);
#endif

/*
 * This function is the entrypoint for the whole game. Its role is to
 * initialize Vulkan, create the renderer and start the game loop.
 */
int platform_run(i32 argc, u8 * *argv)
{
	(void)argc;
	(void)argv;

	log_info("Using Vulkan as rendering backend.\n");

	RGFW_window *win = RGFW_createWindow("topaz", 0, 0, 800, 600, RGFW_windowCenter | RGFW_windowNoResize | RGFW_windowHide);
	RGFW_window_show(win);
	RGFW_window_setExitKey(win, RGFW_escape);
	#ifdef PLATFORM_MACOS
	macos_set_window_layer(win);
	#endif

	struct renderer_context *context = renderer_context_init(win);

	while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
		RGFW_event event;
		while (RGFW_window_checkEvent(win, &event));
	}

	renderer_context_deinit(context);
	RGFW_window_close(win);
	return 0;
}
