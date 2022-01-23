#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

int
main(int argc, char **argv)
{
    for(int i = 0; i < argc; i++) {
        // argv is char **
        // so argv[i] is char *
        // which means we can feed it to puts
        puts(argv[i]);
    }

    return 0;
}
