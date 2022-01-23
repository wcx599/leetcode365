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
    int key;       // for BST left to right ordering
    int priority;  // for heap bottom to top ordering
    size_t size;   // how many nodes in this subtree?
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

// Call this whenever the size field might
// have become invalid.
// Assumes kids have corrects size fields.
static void
treeFixSize(struct node *root)
{
    size_t sum = 1;

    for(int i = 0; i < NUM_KIDS; i++) {
        if(root->kids[i] != 0) {
            sum += root->kids[i]->size;
        }
    }

    root->size = sum;
}

// Rotate child on side up to root
//
//    x        y
//   A y      x C
//     BC    AB
static void
treeRotate(Tree tree, int side)
{
    struct node *x = *tree;
    struct node *y = (*tree)->kids[side];
    struct node *b = y->kids[!side];

    // fix up all the pointers
    *tree = y;
    y->kids[!side] = x;
    x->kids[side] = b;

    // fix sizes, child first
    treeFixSize(x);
    treeFixSize(y);
}

void
treeInsert(Tree tree, int key)
{
    if(*tree) {
        if(key != (*tree)->key) {
            int side = key > (*tree)->key;
            treeInsert(&(*tree)->kids[side], key);
            treeFixSize(*tree);
            // maybe fix heap property
            if((*tree)->kids[side]->priority > (*tree)->priority) {
                // I am in trouble, must rotate kid[side] up
                treeRotate(tree, side);
            }
        }
    } else {
        *tree = malloc(sizeof(struct node));
        assert(*tree);
        (*tree)->key = key;
        (*tree)->priority = rand();
        (*tree)->size = 1;      // no kids, I am only node
        for(int i = 0; i < NUM_KIDS; i++) {
            (*tree)->kids[i] = 0;
        }
    }
}

void
treeDelete(Tree tree, int key)
{
    if(*tree) {
        if((*tree)->key == key) {
            // do I have <2 kids?
            for(int empty = LEFT; empty <= RIGHT; empty++) {
                if((*tree)->kids[empty] == 0) {
                    // I do have <2 kids
                    struct node *deleteMe = *tree;
                    *tree = (*tree)->kids[!empty];
                    free(deleteMe);
                    // and we're done
                    return;
                }
            }
            // If I got here, *tree has two kids.
            // Find higher priority kid and rotate up.
            int side = 
                (*tree)->kids[RIGHT]->priority
                > (*tree)->kids[LEFT]->priority;
            treeRotate(tree, side);

            // delete key from !side
            treeDelete(&((*tree)->kids[!side]), key);
            treeFixSize(*tree);
        } else {
            // recurse into appropriate subtree
            treeDelete(&((*tree)->kids[key > (*tree)->key]), key);
            treeFixSize(*tree);
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
        printf("%d [%zu %08x]\n", root->key, root->size, root->priority);

        //print right subtree
        treePrintInternal(root->kids[RIGHT], depth+1);
    }
}

void
treePrint(Tree tree)
{
    // internal printer indents by depth
    treePrintInternal(*tree, 0);

    size_t size = treeSize(tree);

    // print all elements by finding them by rank
    printf("Elements by rank:");
    for(size_t rank = 0; rank < size; rank++) {
        printf(" %d", treeSearchByRank(tree, rank));
    }
    putchar('\n');
}

size_t
treeSize(Tree tree)
{
    if(*tree == 0) {
        return 0;
    } else {
        return (*tree)->size;
    }
}

int
treeSearchByRank(Tree tree, size_t rank)
{
    assert(rank < treeSize(tree));

    // look at # of element in left subtree
    size_t left = treeSize(&(*tree)->kids[LEFT]);

    if(left == rank) {
        // root has given rank
        return (*tree)->key;
    } else if(left > rank) {
        // recurse into left subtree
        return treeSearchByRank(&(*tree)->kids[LEFT], rank);
    } else {
        // recurse into right subtree
        return treeSearchByRank(&(*tree)->kids[RIGHT], rank - left - 1);
    }
}
