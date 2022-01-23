#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "set.h"

static size_t
hashString(size_t range, const char *s)
{
    size_t h;

    h = 0;
    
    while(*s != '\0') {
        h = h*97 + *s++;
    }

    return h % range;
}

int
main(int argc, char **argv)
{
    struct set *s;
    int i;

    for(i = 1; i < argc; i++) {
        printf("hashString(%s) == %zu\n", argv[i], hashString(100, argv[i]));
    }

    s = setCreate();

    for(i = 0; i < 1000000; i++) {
        setInsert(s, i);
    }

    puts("done inserting");

    for(i = 0; i < 1000000; i++) {
        assert(setMember(s, i));
    }

    puts("done testing membership");

    setDelete(s,5);
    assert(!setMember(s, 5));

    setDestroy(s);

    return 0;
}
