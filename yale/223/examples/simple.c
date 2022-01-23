#include <stdio.h>

/* demonstrate variables and I/O */

int
main(int argc, char **argv)
{
    int c;

    c = getchar();
    printf("The numerical value of '%c' is %d.", c, c);

    return 0;
}
