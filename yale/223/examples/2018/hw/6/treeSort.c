// Read a tree from stdin,
// sort it,
// then write to stdout.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tree.h"

int
main(int argc, char **argv)
{
    Tree *t;

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    t = treeRead(stdin);
    if(t == 0) {
        return 2;
    }

    treeSort(t);
    treeWrite(t, stdout);
    treeDestroy(t);

    return 0;
}
