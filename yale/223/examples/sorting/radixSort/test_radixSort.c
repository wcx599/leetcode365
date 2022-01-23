#include <stdio.h>
#include <assert.h>

#include "radixSort.h"

#define SMALL_N (3)
#define LARGE_N (20)
#define LARGE_LEN (10000)

int
main(int argc, char **argv)
{
    int i;
    int j;
    const char *small[SMALL_N] = { "sat", "bad", "bat" };
    char large[LARGE_N][LARGE_LEN];
    const char *large_refs[LARGE_N];

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    radixSort(SMALL_N, small);

    for(i = 0; i < SMALL_N; i++) {
        puts(small[i]);
    }

    for(i = 0; i < LARGE_N; i++) {
        large_refs[i] = &large[i][0];
        for(j = 0; j < LARGE_LEN-2; j++) {
            large[i][j] = 'a';
        }
        large[i][LARGE_LEN-2] = 'z' - i;
        large[i][LARGE_LEN-1] = '\0';
    }

    radixSort(LARGE_N, large_refs);

    for(i = 0; i < LARGE_N; i++) {
        assert(large_refs[i] == &large[LARGE_N - 1 - i][0]);
    }

    return 0;
}
