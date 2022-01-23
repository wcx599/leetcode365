#include <stdio.h>

/* test what happens with VLAs that are too big */
int
main(int argc, char **argv)
{
    int n;

    if(argc != 2) {
        fprintf(stderr, "Usage: %s size-of-array\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);

    int huge[n];

    huge[0] = 11;
    huge[n-1] = 12;

    return 1;
}
