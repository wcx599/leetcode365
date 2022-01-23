#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "radixSort.h"

#define SIZE_INITIAL (32)
#define SIZE_MULTIPLIER (2)

int
main(int argc, char **argv)
{
    char *word;

    // C is the only modern programming language that forces
    // you to do this from scratch for every data type.
    size_t size = SIZE_INITIAL;
    size_t n = 0;
    char **words = calloc(size, sizeof(char *));
    assert(words);

    while(scanf("%ms", &word) == 1) {
        if(n >= size) {
            size *= SIZE_MULTIPLIER;
            words = realloc(words, sizeof(char *) * size);
            assert(words);
        }

        words[n++] = word;
    }

    radixSort(n, words);

    for(size_t i = 0; i < n; i++) {
        puts(words[i]);
    }

    for(size_t i = 0; i < n; i++) {
        free(words[i]);
    }

    free(words);

    return 0;
}
