#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "tree.h"

#define LEFT (0)
#define RIGHT (1)
#define NUM_KIDS (2)

// a tree is either a null pointer (empty tree)
// or a pointer to a struct node *
struct node {
    int key;
    struct node *kids[NUM_KIDS];
};

Tree
treeCreate(void)
{
    Tree t = calloc(1, sizeof(struct node *));
    assert(t);
    return t;
}

// free the nodes of a tree
static void
treeDestroyInternal(struct node *root)
{
    if(root) {
        // kill the kids first
        for(int i = 0; i < NUM_KIDS; i++) {
            treeDestroyInternal(root->kids[i]);
        }
        free(root);
    }
}

void
treeDestroy(Tree tree)
{
    treeDestroyInternal(*tree);
    free(tree);
}

void
treeInsert(Tree tree, int key)
{
    if(*tree) {
        if(key != (*tree)->key) {
            // tail recursion, could be eliminated
            treeInsert(&(*tree)->kids[key > (*tree)->key], key);
        }
    } else {
        *tree = malloc(sizeof(struct node));
        assert(*tree);
        (*tree)->key = key;
        for(int i = 0; i < NUM_KIDS; i++) {
            (*tree)->kids[i] = 0;
        }
    }
}

static int
treeSearchInternal(struct node *root, int key)
{
    if(root) {
        if(key != root->key) {
            return treeSearchInternal(root->kids[key > root->key], key);
        } else {
            return 1;
        }
    } else {
        return 0;
    }
}

int
treeSearch(Tree tree, int key)
{
    return treeSearchInternal(*tree, key);
}

#define INDENTATION (2)

static void
treePrintInternal(struct node *root, size_t depth)
{
    if(root) {
        // print left subtree
        treePrintInternal(root->kids[LEFT], depth+1);

        // print indented root
        for(size_t i = 0; i < depth * INDENTATION; i++) {
            putchar(' ');
        }
        printf("%d\n", root->key);

        //print right subtree
        treePrintInternal(root->kids[RIGHT], depth+1);
    }
}

void
treePrint(Tree tree)
{
    // internal printer indents by depth
    treePrintInternal(*tree, 0);
}

static size_t
treeSizeInternal(struct node *root)
{
    if(root) {
        return 
            treeSizeInternal(root->kids[LEFT]) 
            + treeSizeInternal(root->kids[RIGHT])
            + 1;
    } else {
        return 0;
    }
}

size_t
treeSize(Tree tree)
{
    return treeSizeInternal(*tree);
}
