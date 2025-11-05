/* SPDX-License-Identifier:BSD-3-Clause */
#include "../renderer.h"
#include "instance.h"
#include "physical_device.h"
#include "device.h"
#include "surface.h"
#include "vk.h"
#include "../../core/arena.h"
#include <stdlib.h>
#include <stdio.h>

struct renderer_context *renderer_context_init(RGFW_window *window)
{
	struct renderer_context *context = (struct renderer_context *)arena_alloc(global_arena, (sizeof(struct renderer_context)));
	context->window = window;

	vk_instance_init(context);
	vk_surface_init(context);
	vk_physical_device_pick(context);
	vk_physical_device_select_family_indices(context);
	vk_device_init(context);
	return context;
}

void renderer_context_deinit(struct renderer_context *context)
{
	vk_surface_deinit(context);
	vk_device_deinit(context);
	vk_instance_deinit(context);
}

struct mesh *renderer_build_chunk_mesh(void)
{
	return NULL;
}

void renderer_draw_mesh(struct renderer_context *context, struct mesh mesh)
{
	(void) context;
	(void)mesh;
}

void renderer_draw_chunk(struct renderer_context *context, struct mesh mesh)
{
	(void)mesh;
	(void)context;
}
