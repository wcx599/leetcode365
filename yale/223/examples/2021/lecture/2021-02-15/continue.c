#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define N (10)

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    // print odd numbers up to N
    for(int i = 0; i < N; i++) {
        if(i % 2 == 0) {
            // skip rest of loop body
            continue;
        }
        printf("(%d)\n", i);
    }

    // continue is less useful in while loops
    int i = 0;

    while(i < N) {
        if(i % 2 == 0) {
            i++;      // we have to add iteration by hand
            continue;
        }

        printf("[%d]\n", i);
        i++;         // duplicate code is usually bad code
    }

    // continue can almost always be replaced by if
    for(int i = 0; i < N; i++) {
        if(i % 2 != 0) {
            printf("{%d}\n", i);
        }
    }


    return 0;
}
