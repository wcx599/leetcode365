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

    // read in a bunch of ints and insert them
    int key;
    Tree tree = treeCreate();
    int target = atoi(argv[1]);

    puts("Initial empty tree");
    treePrint(tree);
    puts("===");

    while(scanf("%d", &key) == 1) {
        printf("Inserting %d\n", key);
        treeInsert(tree, key);
        treePrint(tree);
        printf("=== [%zu elements] Is %d in tree? %d\n", treeSize(tree), target, treeSearch(tree, target));
    }

    treeDestroy(tree);

    return 0;
}
