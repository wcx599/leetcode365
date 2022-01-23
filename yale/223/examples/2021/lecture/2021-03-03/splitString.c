#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

// split input on first space
// so *head points to malloc'd copy of everything before space
// *tail everything after
// explodes if no first space
void
splitString(const char *input, char **head, char **tail)
{
    const char *spaceLocation = strchr(input, ' ');

    assert(spaceLocation);

    // copy into head and tail
    size_t n = spaceLocation - input;
    *head = malloc(n + 1);
    strncpy(*head, input, n);
    (*head)[n] = '\0';

    *tail = malloc(strlen(input) - n);
    strcpy(*tail, input + n + 1);
}


int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    // goal: split s into two strings at first ' '
    const char *s = "split this string please";

    char *h;
    char *t;

    // split s into h and t
    // we pass address so splitString can
    // fill in values
    splitString(s, &h, &t);
  
    puts(h);
    puts(t);

    free(h);
    free(t);

    return 0;
}
