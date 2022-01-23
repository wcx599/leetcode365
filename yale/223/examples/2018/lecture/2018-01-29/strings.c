#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define BUFLEN (1024)

void
putsEncrypted(const char *s)
{
    while(*s) {
        putchar(*s ^ 0xf);
        s++;
    }

    putchar('\n');
}

int
main(int argc, char **argv)
{
    char alphabet[1024]; 

    for(int i = 'a'; i <= 'z'; i++) {
        alphabet[i - 'a'] = i;
    }

    puts(alphabet);

    /* put on terminating '\0' */
    alphabet['z' - 'a' + 1] = '\0';

    puts(alphabet);

    for(int i = 0; i < argc; i++) {
        putsEncrypted(argv[i]);
    }


    return 0;
}
