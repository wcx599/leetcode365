/* Demo program for packed two-dimensional arrays */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct flat2d {
    size_t rows;  // number of rows
    size_t cols;  // number of columns
    int data[];   // data, stored at end of struct
};

// malloc and return flat2d of given dimensions
// array is not initialized!
struct flat2d *
flat2dCreate(size_t rows, size_t cols)
{
    struct flat2d *a;

    a = malloc(sizeof(struct flat2d) + sizeof(int) * rows * cols);

    assert(a);

    a->rows = rows;
    a->cols = cols;

    return a;
}

// free space used by a
void
flat2dDestroy(struct flat2d *a)
{
    free(a);
}

// return a pointer to a[i][j]
// or 0 if i or j is out of bounds
int *
flat2dRef(struct flat2d *a, size_t i, size_t j)
{
    if(i >= a->rows || j >= a->cols) {
        return 0;
    } else {
        return &a->data[i * a->cols + j];
    }
}

int
main(int argc, char **argv)
{
    int rows;
    int cols;
    struct flat2d *a;
    int i;
    int j;

    if(argc != 3) {
        fprintf(stderr, "Usage: %s rows cols\n", argv[0]);
        return 1;
    }
    /* else */

    rows = atoi(argv[1]);
    cols = atoi(argv[2]);

    a = flat2dCreate(rows, cols);

    for(i = 0; i < rows; i++) {
        for(j = 0; j < cols; j++) {
            *flat2dRef(a, i, j) = i - j;
        }
    }

    for(i = 0; i < rows; i++) {
        for(j = 0; j < cols; j++) {
            printf("%4d", *flat2dRef(a, i, j));
        }
        putchar('\n');
    }

    flat2dDestroy(a);

    return 0;
}
