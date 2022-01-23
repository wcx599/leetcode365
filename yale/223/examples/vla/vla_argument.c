#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int mungeArray(int height, int width, int a[height][width])
{
    a[0][0] = 12;
}

int
main(int argc, char **argv)
{
    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    int a[100][100];

    mungeArray(100, 100, a);

    assert(a[0][0] == 12);

    return 0;
}
