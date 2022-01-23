#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>

uint64_t
slowFib(int n)
{
    if(n < 2) {
        return 1;
    } else {
        return slowFib(n-1) + slowFib(n-2);
    }
}

uint64_t
fib(int n)
{
    if(n < 2) {
        return 1;
    } else {
        // make a table of solutions up to and including n
        uint64_t *f = calloc(n+1, sizeof(uint64_t));

        f[0] = f[1] = 1;

        for(int i = 2; i <= n; i++) {
            f[i] = f[i-1] + f[i-2];
        }

        // clean up and return f[n]
        uint64_t result = f[n];
        free(f);
        return result;
    }
}

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    for(int n = 0; n < 80; n++) {
        printf("fib(%d) == %" PRIu64 "\n", n, fib(n));
    }

    // now let's do it the slow way
    for(int n = 0; n < 80; n++) {
        printf("slowFib(%d) == %" PRIu64 "\n", n, slowFib(n));
    }

    return 0;
}
