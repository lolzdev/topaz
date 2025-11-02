// SPDX-License-Identifier: BSD-3-Clause
#include "arena.h"
#include <stdlib.h>

struct arena_allocator *arena_init(usize size)
{
	struct arena_allocator *allocator = (struct arena_allocator *) malloc(sizeof(struct arena_allocator));
	allocator->size = size;
	allocator->base = (usize) malloc(size);
	allocator->position = 0;

	return allocator;
}

void arena_deinit(struct arena_allocator *allocator)
{
	free((void *)allocator->base);
	free((void *)allocator);
}

void *arena_alloc(struct arena_allocator *allocator, usize size)
{
	void *ptr = (void *)(allocator->base + allocator->position);
	allocator->position += size;
	return ptr;
}

void *arena_zalloc(struct arena_allocator *allocator, usize size)
{
	void *ptr = arena_alloc(allocator, size);
	for (usize i=0; i < size; i++) {
		((u8 *)ptr)[i] = 0x0;
	}

	return ptr;
}

void arena_bump(struct arena_allocator *allocator)
{
	allocator->position = 0;
}
