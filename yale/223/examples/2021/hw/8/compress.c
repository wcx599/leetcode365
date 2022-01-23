#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

#include "compressionFormat.h"

#define READ_ALL_BUFFER_INITIAL (1024)
#define READ_ALL_MULTIPLIER (2)

// Return all characters from stream
// as malloc'd string.
//
// Number of characters read is put in *n.
static unsigned char *
readAll(FILE *f, size_t *n)
{
    size_t size = READ_ALL_BUFFER_INITIAL;
    unsigned char *buffer = malloc(size);
    assert(buffer);

    *n = 0;

    int c;

    while((c = getc(f)) != EOF) {

        // grow buffer if needed
        if(*n >= size) {
            size *= READ_ALL_MULTIPLIER;
            buffer = realloc(buffer, size);
            assert(buffer);
        }

        buffer[(*n)++] = c;
    }

    return buffer;
}

struct count {
    unsigned char expansion[COMPRESSED_EXPANSION];
    size_t count;
};

// Compare two struct counts by count fields.
// Bigger value sorts earlier
static int
countCompare(const void *a, const void *b)
{
    return ((struct count *) b)->count - ((struct count *) a)->count;
}

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s < uncompressed-data > compressed-data\n", argv[0]);
        return 1;
    }
    
    // grab entire contents of input
    // since we are going to need two passes
    size_t n;
    unsigned char *s = readAll(stdin, &n);

    // build a table of bigram counts
    // that we can sort
    // all of this assumes COMPRESSED_EXPANSION == 2
    struct count counts[UCHAR_MAX+1][UCHAR_MAX+1];

    for(int i = 0; i <= UCHAR_MAX; i++) {
        for(int j = 0; j <= UCHAR_MAX; j++) {
            counts[i][j].expansion[0] = i;
            counts[i][j].expansion[1] = j;
            counts[i][j].count = 0;
        }
    }

    for(size_t i = 0; i + 1 < n; i++) {
        // There is an optimization here we are not doing.
        // Compressing bigrams that contain high-bit characters
        // is worth more than bigrams with low-bit characters,
        // since we also avoid the escape. But this works reasonably
        // well and I don't want to set the par values too low.
        counts[s[i]][s[i+1]].count++;
    }

    // flattened version of counts
    struct count *flatCounts = (struct count *) counts;

    qsort(flatCounts, (UCHAR_MAX+1)*(UCHAR_MAX+1), sizeof(struct count), countCompare);

    // another table to make things fast
    unsigned char compression[UCHAR_MAX+1][UCHAR_MAX+1];

    for(int i = 0; i <= UCHAR_MAX; i++) {
        for(int j = 0; j <= UCHAR_MAX; j++) {
            compression[i][j] = 0;
        }
    }

    // first COMPRESSED_CHARS entries get compressed
    for(int i = 0; i < COMPRESSED_CHARS; i++) {
        compression[flatCounts[i].expansion[0]][flatCounts[i].expansion[1]] = COMPRESSED_CHAR_MIN + i;
        for(int j = 0; j < COMPRESSED_EXPANSION; j++) {
            putchar(flatCounts[i].expansion[j]);
        }
    }

    // now process the input looking for compressible
    // and escape-needing characters
    for(unsigned char *p = s; p < s + n; p++) {
        if(p + 1 < s + n && compression[p[0]][p[1]]) {
            // can compress
            putchar(compression[p[0]][p[1]]);
            // eat extra character
            p++;
        } else if(*p >= COMPRESSED_CHAR_MIN) {
            // must escape
            putchar(COMPRESSED_CHAR_ESCAPE);
            putchar(*p);
        } else {
            // copy through
            putchar(*p);
        }
    }

    free(s);

    return 0;
}
