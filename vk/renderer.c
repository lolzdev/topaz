/* SPDX-License-Identifier:BSD-3-Clause */
#include "../rendering/renderer.h"
#include "instance.h"
#include "physical_device.h"
#include "device.h"
#include "vk.h"
#include "../core/arena.h"
#include <stdlib.h>
#include <stdio.h>

struct renderer_context *renderer_context_init(void)
{
	struct renderer_context *context = (struct renderer_context *)arena_alloc(global_arena, (sizeof(struct renderer_context)));

	vk_instance_init(context);
	vk_physical_device_pick(context);
	vk_physical_device_select_family_indices(context);
	vk_device_init(context);
	return context;
}

void renderer_context_deinit(struct renderer_context *context)
{
	vk_device_deinit(context);
	vk_instance_deinit(context);
}

struct mesh *renderer_build_chunk_mesh(void)
{
	return NULL;
}

void renderer_draw_mesh(struct mesh mesh)
{
	(void)mesh;
}

void renderer_draw_chunk(struct mesh mesh)
{
	(void)mesh;
}
