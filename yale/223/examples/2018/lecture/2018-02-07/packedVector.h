#ifndef _PACKED_VECTOR_H  /* prevents multiple inclusions */
#define _PACKED_VECTOR_H

#include <stdlib.h>  // for size_t

// "opaque struct" - can pass around pointers, but not access contents
typedef struct vector Vector;

// allocate a new vector of size length
Vector * vectorCreate(size_t length);

// destroy a vector
void vectorDestroy(Vector *v);

// documentation to be supplied later
void vectorSet(Vector *v, size_t index, int value);
int vectorGet(const Vector *v, size_t index);
void vectorPrint(const Vector *v);

#endif
