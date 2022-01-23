#ifndef _HASH_H
#define _HASH_H

// this is adapted from the hash table from the 2018-02-26 lecture

#include "point.h"

// usual opaque struct
typedef struct hash Hash;

// create a hash table with initial size n
// this will grow dynamically if the number of elts gets too big
Hash *hashCreate(size_t n);

void hashDestroy(Hash *h);

void hashSet(Hash *h, Point key, int value);

#define HASH_DEFAULT (' ')

// return value at key or HASH_DEFAULT if not present
int hashGet(const Hash *h, Point key);

// print contents of h
// (mostly for debugging)
void hashPrint(const Hash *h);

#endif
