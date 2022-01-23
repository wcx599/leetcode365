#include <stdio.h>

int
main(int argc, char **argv)
{
#ifdef MESSAGE
    puts(MESSAGE);
#endif

    return 0;
}
