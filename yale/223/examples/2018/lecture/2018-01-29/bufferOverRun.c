#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int
main(int argc, char **argv)
{
    char name[4];

    puts("What is your name?");
    gets(name);  // bad deprecated function that reads into a buffer
    printf("Hi %s\n", name);

    return 0;
}
