#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int **
makeArray2D(int rows, int cols)
{
    int **a;  /* array to return */
    int i;

    /* this sneaky version allocates one gigantic block */
    /* then does address arithmetic to compute all the pointers we need */

    /* allocate everything  as one big block */
    /* we need rows many (int *)-sized values for the row pointers */
    /* plus rows * cols (int)-sized values for the actual data */
    a = malloc(sizeof(int *) * rows + sizeof(int) * rows * cols);
    assert(a);

    /* Construct pointers to individual rows. */
    /* The trick is that a + rows points to the address after the
     * last row pointer, which is where we want to start the data. */
    /* Note that we need the case to change the pointer type. */
    a[0] = (int *) (a + rows);
    for(i = 0; i < rows; i++) {
        /* Because a[0] is an int *,
         * adding cols * i skips ahead sizeof(int) * cols * i bytes */
        a[i] = a[0] + cols * i;
    }

    return a;
}

void
deleteArray2D(int **a)
{
    /* Because we allocated everything as one block, we don't
     * have to do anything clever here. */
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
