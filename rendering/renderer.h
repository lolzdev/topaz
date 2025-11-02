// SPDX-License-Identifier: BSD-3-Clause

#ifndef RENDERER_H
#define RENDERER_H
#include "../types.h"

struct mesh {
	usize index;
	usize size;
};

struct renderer_context;

struct renderer_context *renderer_create_context(void);
struct mesh renderer_build_chunk_mesh();
void renderer_draw_mesh(struct mesh);
void renderer_draw_chunk(struct mesh);

#endif
