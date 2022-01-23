#include <stdio.h>
#include <ctype.h>

/* This program counts the number of digits in its input. */

/*
 *This global variable is not used; it is here only to demonstrate
 * what a global variable declaration looks like.
 */
unsigned long SpuriousGlobalVariable = 127;

int
main(int argc, char **argv)
{
    int c;              /* character read */
    int count = 0;      /* number of digits found */

    while((c = getchar()) != EOF) {
        if(isdigit(c)) {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}
