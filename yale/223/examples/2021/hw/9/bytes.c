#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "bytes.h"

struct bytes {
    size_t len;    // number of stored characters
    size_t size;   // space in block
    unsigned char *data;
};

#define BYTES_INITIAL_SIZE (64)
#define BYTES_MULTIPLIER (2)

// create an empty block
Bytes 
bytesCreate(void)
{
    struct bytes *b = malloc(sizeof(struct bytes));
    assert(b);

    b->len = 0;
    b->size = BYTES_INITIAL_SIZE;
    b->data = malloc(b->size);
    assert(b->data);

    return b;
}

// destroy a block
void
bytesDestroy(Bytes b)
{
    free(b->data);
    free(b);
}

// append an unsigned char
void
bytesAppendChar(Bytes b, unsigned char c)
{
    if(b->len >= b->size) {
        b->size *= BYTES_MULTIPLIER;
        b->data = realloc(b->data, b->size);
        assert(b->data);
    }
    b->data[b->len++] = c;
}

// append a block
void
bytesAppendBytes(Bytes b, Bytes b2)
{
    // since b2 might be big, we will grow to fit
    // rather than just doubling
    size_t newLen = b->len + b2->len;
    if(newLen > b->size) {
        b->size = newLen;
        b->data = realloc(b->data, b->size);
        assert(b->data);
    }

    memcpy(b->data + b->len, b2->data, b2->len);
    b->len = newLen;
}

// get length of block
size_t 
bytesLen(Bytes b)
{
    return b->len;
}

// get contents of block
unsigned char *
bytesData(Bytes b)
{
    return b->data;
}

// write contents to FILE *
void 
bytesWrite(Bytes b, FILE *f)
{
    fwrite(b->data, sizeof(unsigned char), b->len, f);
}
