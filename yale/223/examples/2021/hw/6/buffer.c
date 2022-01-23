#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "buffer.h"

struct buffer {
    struct elt *terminator;   // this always points to the null terminator
    size_t n;                 // number of cursors
    size_t size;              // number of non-null characters
    struct elt *cursors[];    // array of cursor pointers
};

// we store the buffer as a circular doubly-linked list
struct elt {
    struct elt *next;
    struct elt *prev;
    char c;
};

Buffer
bufferCreate(size_t n)
{
    Buffer b = malloc(sizeof(struct buffer) + n * sizeof(struct elt *));
    assert(b);

    b->n = n;
    b->size = 0;

    b->terminator = malloc(sizeof(struct elt));
    assert(b->terminator);

    b->terminator->next = b->terminator->prev = b->terminator;

    for(size_t i = 0; i < n; i++) {
        b->cursors[i] = b->terminator;
    }

    return b;
}

void 
bufferDestroy(Buffer b)
{
    struct elt *e;
    struct elt *next;

    next = b->terminator->next;

    do {
        e = next;
        next = e->next;
        free(e);
    } while(e != b->terminator);

    free(b);
}

void
bufferInsert(Buffer b, size_t i, char c)
{
    if(i >= b->n || c == '\0') {
        return;
    }

    // else
    struct elt *e = malloc(sizeof(struct elt));
    e->c = c;
    e->next = b->cursors[i];
    e->prev = b->cursors[i]->prev;

    // we could write this in terms of b->cursors[i]
    // but this is more symmetric
    e->next->prev = e;
    e->prev->next = e;

    // maintain size invariant
    b->size++;
}

void 
bufferCursorForward(Buffer b, size_t i)
{
    if(i >= b->n || b->cursors[i] == b->terminator) {
        return;
    } else {
        b->cursors[i] = b->cursors[i]->next;
    }
}

void
bufferCursorBack(Buffer b, size_t i)
{
    if(i >= b->n || b->cursors[i] == b->terminator->next) { 
        return;
    } else {
        b->cursors[i] = b->cursors[i]->prev;
    }
}

size_t
bufferCursors(Buffer b)
{
    return b->n;
}

size_t
bufferSize(Buffer b)
{
    return b->size;
}

char *
bufferContents(Buffer b)
{
    char *output = malloc(bufferSize(b) + 1);
    assert(output);

    char *top = output;

    for(struct elt *e = b->terminator->next; e != b->terminator; e = e->next) {
        *top++ = e->c;
    }

    *top++ = '\0';

    return output;
}
