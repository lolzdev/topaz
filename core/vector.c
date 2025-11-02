// SPDX-License-Identifier: BSD-3-Clause
#include "vector.h"
#include "log.h"

struct vector *vector_init(usize size, usize element_size)
{
	struct vector *vector = (struct vector *) malloc(sizeof(struct vector));
	vector->length = 0;
	vector->size = size;
	vector->data = malloc(size * element_size);
	return vector;
}

void *vector_shrink(struct vector *vector, usize element_size)
{
	#ifdef DEBUG
	if (vector->length == 0) log_error("Popping from an empty vector.\n");
	#endif
	vector->length -= 1;
	if (vector->length <= vector->size/3) {
		vector->size = vector->length + vector->length/2;
		vector->data = realloc(vector->data, vector->size * element_size + 1);
	}
	return vector->data;
}

void vector_deinit(struct vector *vector)
{
	free(vector->data);
	free(vector);
}
