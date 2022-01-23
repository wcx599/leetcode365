#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

int **
array2dCreate(size_t rows, size_t cols)
{
    // pointers to rows
    int **a = malloc(sizeof(int *) * rows);

    // sneaky trick: allocate all rows at once
    a[0] = malloc(sizeof(int) * rows * cols);

    // but we have to fill in the rest of the pointers
    for(size_t i = 1; i < rows; i++) {
        a[i] = a[0] + cols * i;
    } 

    return a;
}

void
array2dDestroy(int **a)
{
    free(a[0]);  // free the rows
    free(a);     // free the pointers to rows
}

int
main(int argc, char **argv)
{

    if(argc != 3) {
        fprintf(stderr, "Usage: %s rows cols\n", argv[0]);
        return 1;
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);

    int **a = array2dCreate(rows, cols);

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

    // remember to free data
    array2dDestroy(a);

    return 0;
}
