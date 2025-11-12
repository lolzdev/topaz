/* SPDX-License-Identifier:BSD-3-Clause */
#include "arena.h"
#include "log.h"
#include <stdlib.h>

arena arena_init(usize size)
{
	return (arena){
		.capacity = size,
		.position = 0,
		.memory = malloc(size),
	};
}

void *arena_alloc(arena *a, usize size)
{
	if (a->position + size > a->capacity) return NULL;
	void *ret = (void *)((usize)a->memory + (usize)a->position);
	a->position += size;
	return ret;
}

snapshot arena_snapshot(arena a)
{
	return a.position;
}

void arena_reset_to_snapshot(arena *a, snapshot s)
{
	a->position = s;
}

void arena_reset(arena *a)
{
	arena_reset_to_snapshot(a, 0);
}

void arena_deinit(arena a)
{
	free(a.memory);
}
