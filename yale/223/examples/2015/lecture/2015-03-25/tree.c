#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NUM_CHILDREN (2)
#define LEFT (0)
#define RIGHT (1)

struct tree {
    int key;
    struct tree *child[NUM_CHILDREN];
};

#define EMPTY_TREE (0)

static void
treePrintIndented(const struct tree *root, int depth)
{
    int i;

    if(root) {
        treePrintIndented(root->child[LEFT], depth+1);
        
        /* print root */
        for(i = 0; i < 4*depth; i++) { putchar(' '); }
        printf("%d %p\n", root->key, (void *) root);

        treePrintIndented(root->child[RIGHT], depth+1);
    }
}

/* prints out a tree */
void
treePrint(const struct tree *root)
{
    treePrintIndented(root, 0);
    puts("===");
}

/* insert a new element into a tree */
void
treeInsert(struct tree **root, int key)
{
    int i;

    if(*root) {
        if((*root)->key == key) {
            return;
        } else {
            treeInsert(&(*root)->child[(*root)->key < key], key);
        }
    } else {
        *root = malloc(sizeof(**root));
        (*root)->key = key;
        for(i = 0; i < NUM_CHILDREN; i++) { (*root)->child[i] = 0; }
    }
}

/* return 1 if target is in tree, 0 otherwise */
int
treeContains(const struct tree *root, int target)
{
    if(root == 0) {
        return 0;
    } else if(root->key == target) {
        return 1;
    } else {
        return treeContains(root->child[root->key < target], target);
    }
}

/* delete root node */
static void
treeDeleteRoot(struct tree **root)
{
    struct tree *child;
    struct tree **leftmost;

    if(*root == 0) {
        /* no root */
        return;
    } else if((*root)->child[RIGHT] == 0) {
        /* no right child, promote left child */
        child = (*root)->child[LEFT];
        free(*root);
        *root = child;
    } else {
        /* have a right child, find pointer to leftmost descendant */
        for(leftmost = &(*root)->child[RIGHT];
                (*leftmost)->child[LEFT] != 0;
                leftmost = &(*leftmost)->child[LEFT]);

        /* *leftmost is now leftmost descendant */
        (*root)->key = (*leftmost)->key;
        child = *leftmost;
        *leftmost = child->child[RIGHT];
        free(child);
    }
}

        
        





int
main(int argc, char **argv)
{
    int i;
    const int n = 16;
    struct tree handBuiltroot;
    struct tree handBuiltLeft;

    struct tree *root = EMPTY_TREE;

    handBuiltroot.key = 3;
    handBuiltroot.child[LEFT] = &handBuiltLeft;
    handBuiltroot.child[RIGHT] = 0;

    handBuiltLeft.key = 1;
    handBuiltLeft.child[LEFT] = handBuiltLeft.child[RIGHT] = 0;

    treePrint(&handBuiltroot);

    /* new improved tree using treeInsert */
    for(i = 0; i < n; i++) {
        treeInsert(&root, 5*i % n);
        treePrint(root);
    }

    /* get rid of root */
    for(i = 0; i < n; i++) {
        treeDeleteRoot(&root);
        treePrint(root);
    }

    return 0;
}
