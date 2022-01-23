#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <ctype.h>

#include "wordBuffer.h"

struct wordBuffer {
    FILE *f;
    size_t size;   // size of buffer
    char *buffer;
};

#define BUFFER_INITIAL_SIZE (32)
#define BUFFER_MULTIPLIER (2)

WordBuffer
wordBufferCreate(FILE *f)
{
    WordBuffer w = malloc(sizeof(*w));
    assert(w);

    w->f = f;
    w->size = BUFFER_INITIAL_SIZE;
    w->buffer = malloc(w->size);
    assert(w->buffer);

    return w;
}

void
wordBufferDestroy(WordBuffer w)
{
    free(w->buffer);
    free(w);
}

const char *
wordBufferNextWord(WordBuffer w)
{
    // skip any non-alphas
    int c;

    while((c = getc(w->f)) != EOF && !isalpha(c)) { ; }
    ungetc(c, w->f);

    // read until we hit EOF or a nonalpha
    size_t top = 0;

    while((c = getc(w->f)) != EOF && isalpha(c)) {
        // make sure we have enough room for c and '\0'
        if(top + 1 >= w->size) {
            w->size *= BUFFER_MULTIPLIER;
            w->buffer = realloc(w->buffer, w->size);
            assert(w->buffer);
        }

        w->buffer[top++] = c;
    }

    // push back extra char
    ungetc(c, w->f);

    // did we hit EOF?
    if(c == EOF && top == 0) {
        // yes
        return 0;
    } else {
        // no
        // add null
        w->buffer[top] = '\0';
        return w->buffer;
    }
}
