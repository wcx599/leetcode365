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

    char name[10];

    puts("what is your name?");

    // dangerous! can write off the end of the buffer
    gets(name);

    printf("hi %s\n", name);

    return 0;
}
