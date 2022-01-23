#include <stdio.h>

int
main(int argc, char **argv)
{
#if VERBOSITY >= 3 && defined(SAY_HI)
    puts("Hi!");
#endif

    return 0;
}
