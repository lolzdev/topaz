// SPDX-License-Identifier: BSD-3-Clause
#include "../rendering/renderer.h"
#include <vulkan/vulkan.h>
#include "instance.h"
#include "vk.h"
#include <stdlib.h>

struct renderer_context *renderer_context_init(void)
{
	struct renderer_context *context = (struct renderer_context *) malloc(sizeof(struct renderer_context));

	vk_instance_init(context);
	return context;
}

struct mesh *renderer_build_chunk_mesh(void)
{
	return NULL;
}

void renderer_draw_mesh(struct mesh mesh)
{
	(void) mesh;
}

void renderer_draw_chunk(struct mesh mesh)
{
	(void) mesh;
}
