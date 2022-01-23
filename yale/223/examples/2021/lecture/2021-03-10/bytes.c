#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "bytes.h"

// a bytes object is an array of bytes

struct bytes {
    // invariant: n is the size of data not including '\0'
    // invariant: data[n] = '\0'

    size_t n;    // number of bytes in the array
    char *data;  // actual data, plus extra '\0' at end
};

// make a bytes object of given size
Bytes 
bytesCreate(size_t n)
{
    // size is header + data + extra null
    Bytes b = malloc(sizeof(struct bytes));

    b->n = n;   // same as (*b).n = n
    b->data = malloc(n+1);
    b->data[n] = '\0';

    return b;
}

// always build a destructor
void
bytesDestroy(Bytes b)
{
    free(b->data);
    free(b);
}

// resize
void
bytesResize(Bytes b, size_t n)
{
    // call realloc
    b->data = realloc(b->data, n+1);

    // fix null pointer
    b->data[n] = '\0';
}

// access data
char *
bytesData(Bytes b)
{
    return b->data;
}

// access length
size_t
bytesLength(Bytes b)
{
    return b->n;
}

// print bytes as string
void
bytesPut(Bytes b)
{
    puts(bytesData(b));
}

// convert string and convert to bytes
Bytes 
bytesFromString(const char *s)
{
    Bytes b = bytesCreate(strlen(s));
    
    strcpy(bytesData(b), s);

    return b;
}
