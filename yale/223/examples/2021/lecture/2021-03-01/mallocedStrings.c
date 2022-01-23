#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

// returns a malloc'd copy of its argument
// caller is responsible for freeing return value!
// (strdup)
char *
allocStrcpy(const char *s)
{
    char *s2;

    // allocate space for target
    s2 = malloc(sizeof(char) * (strlen(s)+1));
    assert(s2);  // detect malloc failure

    // always works
    strcpy(s2, s);

    return s2;
}


int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    // make a copy of a string constant to modify it
    char *copy = allocStrcpy("hi there!");

    puts(copy);
    copy[0] = 'b';
    puts(copy);

    // don't do this, clobbers malloc header
    // strcpy(copy - 12, "ha ha i destroy your data");

    free(copy);

    // don't do this, already freed
    // copy[1] = 'o';
    // puts(copy);

    // 0x12 is not a legal address to write to
    // strcpy((char *) 0x12, "hi");

    return 0;
}
