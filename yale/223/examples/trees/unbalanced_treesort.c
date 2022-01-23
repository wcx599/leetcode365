#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* simple implementation of TreeSort using an unbalanced
 * binary search tree */

/* node of a tree */
/* a tree is represented by a root node */
/* note this means we can't represent empty trees */
struct node {
    int key;
    struct node *left;
    struct node *right;
};

/* search for a key */
/* returns 1 if present, 0 otherwise */
int
treeSearch(struct node *root, int key)
{
    while(root != 0) {
        if(key == root->key) {
            return 1;
        } else if(key < root->key) {
            root = root->left;
        } else {
            /* key > root->key */
            root = root->right;
        }
    }

    /* didn't find it */
    return 0;
}

/* create a new tree with exactly one key */
struct node *
treeCreate(int key)
{
    struct node *root;

    root = malloc(sizeof(struct node));
    assert(root);

    root->key = key;
    root->left = root->right = 0;

    return root;
}

/* insert a node as a new leaf */
void
treeInsert(struct node *root, int key)
{
    /* if root is null, we are doomed */
    assert(root != 0);

    for(;;) {
        if(key == root->key) {
            /* already present */
            return;
        } else if(key < root->key) {
            if(root->left == 0) {
                root->left = treeCreate(key);
                return;
            } else {
                root = root->left;
            }
        } else {
            /* key > root->key */
            if(root->right == 0) {
                root->right = treeCreate(key);
                return;
            } else {
                root = root->right;
            }
        }
    }
}

/* free a tree */
void
treeDestroy(struct node *root)
{
    if(root != 0) {
        treeDestroy(root->left);
        treeDestroy(root->right);
        free(root);
    }
}

/* compute the number of keys in a tree */
size_t
treeSize(struct node *root) 
{
    if(root != 0) {
        return treeSize(root->left) + treeSize(root->right) + 1;
    } else {
        return 0;
    }
}

/* write the elements of a tree to an array */
/* it is the caller's responsibility to make sure
 * this array is big enough to hold treeSize(root) ints */
/* returns the number of elements written */
int
treeElements(struct node *root, int a[])
{
    int leftSize;

    if(root != 0) {
        leftSize = treeElements(root->left, a);
        a[leftSize] = root->key;
        return leftSize + 1 + treeElements(root->right, a + leftSize + 1);
    } else {
        return 0;
    }
}

#define N (97)
#define MULTIPLIER (14)

int
main(int argc, char **argv)
{
    struct node *tree;
    int sorted[N];
    int i;

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    /* create a tree and fill it */
    tree = treeCreate(0);

    for(i = 1; i < N; i++) {
        /* this gets the numbers out of order */
        treeInsert(tree, (i*MULTIPLIER)%N);
    }

    printf("%d elements\n", treeElements(tree, sorted));

    for(i = 0; i < N; i++) {
        printf("%d ", sorted[i]);
    }
    putchar('\n');

    return 0;
}
