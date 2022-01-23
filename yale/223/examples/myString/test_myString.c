#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "myString.h"

int
main(int argc, char **argv)
{
    struct string *s;

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    s = makeString("hi there");
    assert(stringLength(s) == 8);
    assert(stringCharAt(s, 9) == -1);
    assert(stringCharAt(s, -1) == -1);
    assert(stringCharAt(s, 3) == 't');
    assert(stringCharAt(s, 9) == -1);

    destroyString(s);

    return 0;
}
