// SPDX-License-Identifier: BSD-3-Clause

#ifndef RENDERER_H
#define RENDERER_H
#include "../types.h"

struct mesh {
	usize index;
	usize size;
};

struct renderer_context;

struct renderer_context *renderer_context_init(void);
struct mesh *renderer_build_chunk_mesh(void);
void renderer_draw_mesh(struct mesh mesh);
void renderer_draw_chunk(struct mesh mesh);

#endif
