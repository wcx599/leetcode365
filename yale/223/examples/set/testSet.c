#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "set.h"

int
main(int argc, char **argv)
{
    int i;
    Set s;

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    s = setCreate(sizeof(int));

    for(i = 0; i < 100; i++) {
        assert(!setContains(s, &i));
    } 

    for(i = 0; i < 100; i++) {
        setInsert(s, &i);
    }

    for(i = 0; i < 100; i++) {
        assert(setContains(s, &i));
    } 

    for(i = 100; i < 200; i++) {
        assert(!setContains(s, &i));
    } 

    setDestroy(s);

    return 0;
}
