#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* initialize the application */
void
init(void)
{
    int x;

    x = *((int *) 0xbad1dea); /* if we are lucky, maybe the optimizer will remove it? */
}

int
main(int argc, char **argv)
{
    init();

#ifdef DEBUGGING_OUTPUT
    /*
     * this type of debugging output is not recommended
     * but if you do it anyway:
     *
     * 1. Use stderr, which flushes automatically.
     * 2. Be wary of buffered data on stdout.
     * 3. Wrap your debugging statement in an #ifdef,
     *    so it is not active by default.
     */
    fputs("Returned from init() in main()\n", stderr);
#endif

    return 0;
}
