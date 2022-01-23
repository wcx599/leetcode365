#include <stdio.h>

int
main(int argc, char **argv)
{
    int i;

    for(i = -256; i < 512; i++) {
        putchar(i);
    }

    return 0;
}
