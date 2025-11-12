/* SPDX-License-Identifier:BSD-3-Clause */

#include <stdio.h>
#include "platform.h"
#include "core/arena.h"
#include "core/types.h"

i32 main(i32 argc, char **argv)
{
	u32 result = platform_run(argc, argv);
	return result;
}
