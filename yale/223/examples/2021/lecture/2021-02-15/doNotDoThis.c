#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    // I hate for loops so I will use goto instead
    int i = 0;

    // Look how much more horrible this is than a for loop
startOfLoop:
    // put test at top
    if(i < 10) {
        printf("%d\n", i);

        // update i
        i++;

        // jump to top
        goto startOfLoop;
    }

    return 0;
}
