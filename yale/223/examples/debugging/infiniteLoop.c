#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int
main(int argc, char **argv)
{
    int i;

    for(i = 0; i < 10; i += 0) {
        i *= 37;
    }

    return 0;
}
