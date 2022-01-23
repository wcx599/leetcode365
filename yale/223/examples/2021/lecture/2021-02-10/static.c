#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

int
counter(void)
{
    static int count = 0;

    return count++;
}

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    for(;;) {
        printf("%d\n", counter());
    }

    return 0;
}
