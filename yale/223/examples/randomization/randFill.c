#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "randFill.h"

void
randFill(void *buffer, size_t len)
{
    static FILE *urandom = 0;
    size_t bytesRead;  /* how many bytes did we read so far? */

    if(urandom == 0) {
        urandom = fopen("/dev/urandom", "rb");
        assert(urandom);
    }

    for(bytesRead = 0; bytesRead < len; bytesRead = fread(buffer + bytesRead, 1, len - bytesRead, urandom));
}

#ifdef TEST_MAIN
int
main(int argc, char **argv)
{
    int n;
    int i;
    int r;

    n = atoi(argv[1]);

    for(i = 0; i < n; i++) {
        randFill(&r, sizeof(r));
        printf("%u\n", r);
    }

    return 0;
}
#endif
