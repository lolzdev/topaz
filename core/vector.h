/* SPDX-License-Identifier:BSD-3-Clause */
#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include "../core/types.h"

/*
 * The vector is a dynamically growing array that can be operated as a regular
 * array by accessing its `data` member and as a stack using `vector_push()`
 * and `vector_pop()`.
 */
struct vector {
	usize length, size;
	void *data;
};

/*
 * Create a new vector with starting capacity of `size` where each element has
 * size `element_size`.
 */
struct vector *vector_init(usize size, usize element_size);
void vector_deinit(struct vector *vector);

/*
 * This function reduces the lenth of the vector thus removing the last
 * element. If the used memory (length) is less than 1/3 of the allocated
 * memory (size) the memory is reallocated to fit 1.5x the new length. Consider
 * using the `vector_pop()` macro instead.
 */
void *vector_shrink(struct vector *vector, usize element_size);

/*
 * Push `value` on the vector. If there isn't enough allocated memory,
 * reallocate the internal array to be 1.5x the current size and copy all the
 * elements to the new allocated memory.
 */
#define vector_push(vec, T, value) do {\
	if ((vec)->length + 1 >= (vec)->size) {\
		(vec)->size += (vec)->size/2 > 0 ? (vec)->size / 2 : 1;\
		(vec)->data = realloc((vec)->data, (vec)->size * sizeof(T));\
	}\
	((T *)(vec)->data)[(vec)->length] = value;\
	(vec)->length += 1;\
} while (0)

/*
 * Return the last element of the vector and calls `vector_shrink()`. Check out
 * that function description.
 */
#define vector_pop(vector, T) (((T*)vector_shrink((vector), sizeof(T)))[vector->length])

#endif
