#include <stdio.h>
#include <stdlib.h>

/* demonstrates use of two-dimensional variable length array in C99 */

int
main(int argc, char **argv)
{
    int x;
    int y;

    if(argc != 3) {
        fprintf(stderr, "Usage: %s x y\n", argv[0]);
        return 1;
    }

    x = atoi(argv[1]);
    y = atoi(argv[2]);

    /* this allocates the array of width x and height y */
    int table[x][y];
    
    /* fill it in with a multiplication table */
    for(int i = 0; i < x; i++) {
        for(int j = 0; j < y; j++) {
            table[i][j] = i*j;
        }
    }

    /* now print it out */
    for(int i = 0; i < x; i++) {
        for(int j = 0; j < y; j++) {
            printf("%4d", table[i][j]);
        }
        putchar('\n');
    }

    return 0;
}
