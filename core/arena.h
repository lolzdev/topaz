// SPDX-License-Identifier: BSD-3-Clause
#ifndef ARENA_H
#define ARENA_H

#include "../types.h"

/*
 * An arena is a fast allocator that just
 * keeps everything in a contiguous chunk
 * of memory and moves a "pointer" when
 * allocating new memory. The allocated
 * memory is then free'd all at once.
 */
struct arena_allocator {
	usize size;
	usize base;
	usize position;
};


/* Create a new arena allocator of size `size` */
struct arena_allocator *arena_init(usize size);
/* Destroy the allocator and */
void arena_deinit(struct arena_allocator *allocator);

/*
 * Allocate a chunk of memory of size `size` on the
 * arena.
 */
void *arena_alloc(struct arena_allocator *allocator, usize size);
/*
 * Same as `arena_alloc()` but also set all the allocated
 * memory to zero.
 */
void *arena_zalloc(struct arena_allocator *allocator, usize size);
/*
 * Free all the allocated memory at once.
 * This just sets the allocator cursor to its
 * starting position.
 */
void arena_bump(struct arena_allocator *allocator);

#endif
