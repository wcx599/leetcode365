#include <stdio.h>
#include <assert.h>

int
main(int argc, char **argv)
{
    puts("warning!");

    for(int i = 20; i > 0; i--) {
        printf("Decimal: %d Hex: %x (100%%)\n", i, i);
    }

    puts("BOOM!");

    printf("BOOM BOOM\n");

    return 0;
}
