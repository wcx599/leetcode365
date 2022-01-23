#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Demonstrate that atoi(argv[1]) is NOT PRIME
 * by showing that NO CANDIDATE FACTORIZATION WORKS!
 *
 * (If it is prime, slink quietly away when we find the working factorization.)
 */

int
main(int argc, char **argv)
{
    int i;
    int j;
    int n;

    if(argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);

    for(i = 2; i < n; i++) {
        for(j = 2; j < n; j++) {
            if(i * j == n) {
                /* Our plot is foiled!  Sneak off before anybody notices. */
                /* Unlike break, this leaves both loops */
                puts("Curses!  Time to make my escape...");
                goto leaveBothLoops;
            }
            printf("%d*%d == %d != %d\n", i, j, i*j, n);
        }
    }

leaveBothLoops:
    return 0;
}
