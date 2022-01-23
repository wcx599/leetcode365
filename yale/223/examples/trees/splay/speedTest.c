#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tree.h"

int
main(int argc, char **argv)
{
    int i;
    int n;
    struct tree *t = TREE_EMPTY;

    if(argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return 1;
    }

    /* insert n random ints */
    n = atoi(argv[1]);

    for(i = 0; i < n; i++) {
        treeInsert(&t, rand());
    }

    treeDestroy(&t);

    return 0;
}
