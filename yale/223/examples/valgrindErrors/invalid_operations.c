#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int
main(int argc, char **argv)
{
    char *s;

    s = malloc(1);
    s[0] = 'a';
    s[1] = '\0';

    puts(s);

    return 0;
}
