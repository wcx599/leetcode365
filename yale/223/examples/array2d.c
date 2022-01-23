#include <stdio.h>
#include <stdlib.h>

/* two-dimensional array experiments */

int
main(int argc, char **argv)
{
    int a[16][8];

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    printf("%p\n", a);
    printf("%p\n", a[1]);

    return 0;
}
