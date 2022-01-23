#include <stdio.h>

/* compute a simple checksum of its input */

int
main(int argc, char **argv)
{
    unsigned int checksum;
    int c;

    checksum = 0;

    while((c = getchar()) != EOF) {
        /* add numerical code of next character to checksum */
        checksum += c;
    }

    printf("%u\n", checksum);

    return 0;
}
