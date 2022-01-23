#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    int c;

    while((c = getchar()) != EOF) {
        switch(c) {
            case 'e':
            case 'E':
                // do nothing
                break;
            case 'O':
                printf("This used to be O->");
                // fall through
            case 'o':
                putchar('a');
                break;
            default:
                putchar(c);
                break;
        }
    }

    return 0;
}
