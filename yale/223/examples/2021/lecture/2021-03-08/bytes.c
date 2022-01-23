#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "bytes.h"

// a bytes object is an array of bytes

struct bytes {
    size_t n;    // number of bytes in the array
    char data[]; // actual data, plus extra '\0' at end
};

// make a bytes object of given size
struct bytes *
bytesCreate(size_t n)
{
    // size is header + data + extra null
    struct bytes *b = malloc(sizeof(struct bytes) + n + 1);

    b->n = n;
    b->data[n] = '\0';

    return b;
}

// always build a destructor
void
bytesDestroy(struct bytes *b)
{
    free(b);
}

// access data
char *
bytesData(struct bytes *b)
{
    return b->data;
}

// access length
size_t
bytesLength(struct bytes *b)
{
    return b->n;
}

// print bytes as string
void
bytesPut(struct bytes *b)
{
    puts(bytesData(b));
}

// convert string and convert to bytes
struct bytes *
bytesFromString(const char *s)
{
    struct bytes *b = bytesCreate(strlen(s));
    
    strcpy(bytesData(b), s);

    return b;
}
