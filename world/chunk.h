#ifndef CHUNK_H
#define CHUNK_H

#include "block.h"

#define CHUNK_SIZE 16
#define CHUNK_INDEX(x, y, z) (CHUNK_SIZE * CHUNK_SIZE * (x) + CHUNK_SIZE * (y) + (z))

typedef usize chunk_position[2];

/*
 * Chunk are a group of blocks with
 * size 16x16x16. The world is composed
 * of infinite chunks in each axis.
 */
struct chunk {
	block_id blocks[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
	chunk_position position;
};

#endif
