#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "avlTree.h"

int
main(int argc, char **argv)
{
    AvlTree t;
    int i;

    t = AVL_EMPTY;

    assert(avlSearch(t, 12) == 0);
    avlInsert(&t, 12);
    assert(avlSearch(t, 12) == 1);
    avlDestroy(t);

    t = AVL_EMPTY;
    for(i = 0; i < 100; i++) {
        assert(avlSearch(t, i) == 0);
        avlInsert(&t, i);
        assert(avlSearch(t, i) == 1);
    }

    for(i = 0; i < 100; i++) {
        assert(avlSearch(t, i) == 1);
        avlInsert(&t, i);
        assert(avlSearch(t, i) == 1);
    }
      
    avlDestroy(t);

    t = AVL_EMPTY;
    for(i = 0; i < 10000000; i += 2) {
        assert(avlSearch(t, i) == 0);
        avlInsert(&t, i);
        assert(avlSearch(t, i+1) == 0);
        assert(avlSearch(t, i) == 1);
    }

    avlDestroy(t);

    return 0;
}
