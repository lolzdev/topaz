/* SPDX-License-Identifier:BSD-3-Clause */

#include <stdio.h>
#include "platform.h"
#include "core/arena.h"
#include "core/types.h"

struct arena_allocator *global_arena = NULL;

i32 main(i32 argc, char **argv)
{
	global_arena = arena_init(1);
	u32 result = platform_run(argc, argv);
	arena_bump(global_arena);
	arena_deinit(global_arena);
	return result;
}
