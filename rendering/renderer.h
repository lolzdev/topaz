// SPDX-License-Identifier: BSD-3-Clause

#ifndef RENDERER_H
#define RENDERER_H
#include "../types.h"

/*
 * A mesh is a drawable object represented
 * as an index (offset) in the global vertex
 * and index buffers and a size.
 */
struct mesh {
	usize vertex_offset;
	usize index_offset;
	usize size;
};

/* The renderer context stores objects
 * related to rendering. Implementation
 * depends on the graphics backend used
 * so for reference see gl/gl.h or vk/vk.h
 */
struct renderer_context;

struct renderer_context *renderer_context_init(void);
void renderer_context_deinit(struct renderer_context *context);
struct mesh *renderer_build_chunk_mesh(void);
void renderer_draw_mesh(struct mesh mesh);
void renderer_draw_chunk(struct mesh mesh);

#endif
