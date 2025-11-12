/* SPDX-License-Identifier:BSD-3-Clause */
#ifndef ARENA_H
#define ARENA_H
#include "../types.h"

typedef struct {
	usize capacity;
	usize position;
	void* memory;
} arena;

typedef usize snapshot;

/*
 * NOTE(ernesto): faulty initialization is signalided by the arena.memory
 * being null. It is the responsability of the caller to check for fulty
 * initialization.
 */
arena arena_init(usize size);
/*
 * Returns null on unsuccessfull allocation.
 * In this implemention an allocation is only unsuccessfull if the arena
 * does not have enough memory to allocate the requested space
 */
void *arena_alloc(arena *a, usize size);
snapshot arena_snapshot(arena a);
void arena_reset_to_snapshot(arena *a, snapshot s);
void arena_reset(arena *a);
/* This call should never fail, also, do we even care if it does? */
void arena_deinit(arena a);
#endif
