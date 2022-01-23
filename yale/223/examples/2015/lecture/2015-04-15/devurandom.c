#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void
randFill(void *buf, size_t len)
{
    static FILE *urandom = 0;
    size_t got;

    if(urandom == 0) {
        urandom = fopen("/dev/urandom", "rb");
        assert(urandom);
    }

    got = fread(buf, 1, len, urandom);

    assert(got == len);
}

int
badPrng(void)
{
    static int nextValue = 12;

    return nextValue = nextValue * 97 + 37;
}

int
main(int argc, char **argv)
{
    int seed;
    int i;
    unsigned int r;
    int n = 10;

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

#ifdef USE_RAND
    randFill(&seed, sizeof(seed));
    srand(seed);
    for(i = 0; i < n; i++) { printf("%d\n", rand()); }
#else
    for(i = 0; i < n; i++) { 
        randFill(&r, sizeof(r));
        printf("%u\n", rand()); 
    }
#endif

    return 0;
}
