#include <stdio.h>

/* doesn't work */
void
doubler(int x)
{
    x *= 2;
}

int
main(int argc, char **argv)
{
    int y;

    y = 1;

    doubler(y);                 /* no effect on y */

    printf("%d\n", y);          /* prints 1 */

    return 0;
}
