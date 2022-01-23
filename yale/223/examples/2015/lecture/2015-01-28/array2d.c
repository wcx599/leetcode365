#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int **
makeArray2D(int rows, int cols)
{
    int **a;  /* array to return */
    int i;

    /* allocate array of pointers to rows */
    a = malloc(sizeof(int *) * (rows+1));  /* 1 extra for sentinel */
    assert(a);

    /* allocate individual rows */
    for(i = 0; i < rows; i++) {
        a[i] = malloc(sizeof(int) * cols);
        assert(a);
    }

    /* put in sentinel */
    a[rows] = 0;

    return a;
}

void
deleteArray2D(int **a)
{
    int i;

    /* free all the rows */
    for(i = 0; a[i] != 0; i++) {
        free(a[i]);
    }

    free(a);
}

/* return an array where a[i][j] = i*j */
int **
makeMultiplicationTable(int rows, int cols)
{
    int **a;
    int i;
    int j;

    a = makeArray2D(rows, cols);

    for(i = 0; i < rows; i++) {
        for(j = 0; j < cols; j++) {
            a[i][j] = i*j;
        }
    }

    return a;
}

/* print first rows*cols subarray of a 2-d array */
void
printArray2D(int **a, int rows, int cols)
{
    int i;
    int j;

    for(i = 0; i < rows; i++) {
        for(j = 0; j < cols; j++) {
            printf("%6d ", a[i][j]);
        }
        putchar('\n');
    }
}

int
main(int argc, char **argv)
{
    int **a;
    int rows;
    int cols;

    if(argc != 3) {
        fprintf(stderr, "Usage: %s rows cols\n", argv[0]);
        return 1;
    }

    rows = atoi(argv[1]);
    cols = atoi(argv[2]);

    a = makeArray2D(rows, cols);
    /* printArray2D(a, rows, cols); */
    deleteArray2D(a);

    putchar('\n');

    a = makeMultiplicationTable(rows, cols);
    printArray2D(a, rows, cols);
    deleteArray2D(a);

    return 0;
}
