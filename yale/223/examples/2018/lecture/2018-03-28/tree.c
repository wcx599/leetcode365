#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

struct tree {
    int key;
    struct tree *left;
    struct tree *right;
};

// generate a random binary search tree
// with keys in range [lo,hi)
struct tree *
treeMakeRandom(int lo, int hi)
{
    struct tree *t;

    if(hi <= lo) {
        // return an empty tree
        return 0;
    } else {
        // pick random element from the middle to be
        // key in the root
        int mid = lo + rand() % (hi - lo);

        t = malloc(sizeof(struct tree));
        t->key = mid;
        t->left = treeMakeRandom(lo, mid);
        t->right = treeMakeRandom(mid+1, hi);

        return t;
    }
}

void
treePrintHelper(const struct tree *t, int depth)
{
    if(t == 0) {
        return;
    }

    treePrintHelper(t->left, depth+1);

    // print indented root
    for(int i = 0; i < depth; i++) {
        putchar(' ');
    }

    printf("%d\n", t->key);

    treePrintHelper(t->right, depth+1);
}

void
treePrint(const struct tree *t)
{
    treePrintHelper(t, 0);
}

int
treeSize(const struct tree *t)
{
    if(t == 0) {
        return 0;
    } else {
        return 1 + treeSize(t->left) + treeSize(t->right);
    }
}

int
treeHeight(const struct tree *t)
{
    if(t == 0) {
        return -1;
    } else {
        int l = treeHeight(t->left);
        int r = treeHeight(t->right);
        return 1 + ((l > r) ? l : r);
    }
}

int
main(int argc, char **argv)
{
    if(argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return 1;
    }

    srand(time(0));

    struct tree *t = treeMakeRandom(0, atoi(argv[1]));
    treePrint(t);
    printf("size = %d\n", treeSize(t));
    printf("height = %d\n", treeHeight(t));

    return 0;
}
