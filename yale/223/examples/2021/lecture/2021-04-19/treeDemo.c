#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "tree.h"

int
main(int argc, char **argv)
{

    if(argc != 2) {
        fprintf(stderr, "Usage: %s target\n", argv[0]);
        return 1;
    }

    // read in a bunch of keys
    // for each key x, insert x if x > 0,
    // delete -x if x < 0
    int key;
    Tree tree = treeCreate();
    int target = atoi(argv[1]);

    puts("Initial empty tree");
    treePrint(tree);
    puts("===");

    while(scanf("%d", &key) == 1) {
        if(key > 0) {
            printf("Inserting %d\n", key);
            treeInsert(tree, key);
        } else if(key < 0) {
            printf("Deleting %d\n", -key);
            treeDelete(tree, -key);
        }
        treePrint(tree);
        printf("=== [%zu elements] Is %d in tree? %d\n", treeSize(tree), target, treeSearch(tree, target));
    }

    treeDestroy(tree);

    return 0;
}
