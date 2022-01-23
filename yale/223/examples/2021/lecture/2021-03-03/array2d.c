#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

int
main(int argc, char **argv)
{

    if(argc != 3) {
        fprintf(stderr, "Usage: %s rows cols\n", argv[0]);
        return 1;
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);

    // here we will demonstrate why C99 variable-length arrays
    // are a trap for the unwary
    int a[rows][cols];

    // set contents
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            a[i][j] = i+j;
        }
    }

    // print contents
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            printf("%4d ", a[i][j]);
        }
        putchar('\n');
    }

    return 0;
}
