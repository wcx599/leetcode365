#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <limits.h>

#define NUM_CHILDREN (2)

#define LEFT (0)
#define RIGHT (1)

// Invariants: 
// - Every key below child[LEFT] < key < every key below child[RIGHT]
// - Every heapKey in both subtrees < heapKey.
// heapKeys are chosen randomly to ensure balance with high probability.
struct tree {
    int key;
    int heapKey;
    struct tree *child[NUM_CHILDREN];
};

void
treePrintHelper(const struct tree *t, int depth)
{
    if(t == 0) {
        return;
    }

    treePrintHelper(t->child[LEFT], depth+1);

    // print indented root
    for(int i = 0; i < depth; i++) {
        putchar(' ');
    }

    printf("%d [%d]\n", t->key, t->heapKey);

    treePrintHelper(t->child[RIGHT], depth+1);
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
        return 1 + treeSize(t->child[LEFT]) + treeSize(t->child[RIGHT]);
    }
}

int
treeHeight(const struct tree *t)
{
    if(t == 0) {
        return -1;
    } else {
        int l = treeHeight(t->child[LEFT]);
        int r = treeHeight(t->child[RIGHT]);
        return 1 + ((l > r) ? l : r);
    }
}

// return 1 if it finds key, 0 otherwise
int
treeSearch(const struct tree *t, int key)
{
    if(t == 0) {
        // no key!
        return 0;
    } else if(key == t->key) {
        // found it
        return 1;
    } else if(key < t->key) {
        // look in left
        return treeSearch(t->child[LEFT], key);
    } else {
        // look in right
        return treeSearch(t->child[RIGHT], key);
    }
}

// return largest element <= key
// or INT_MIN if there is no such element.
int
treeSearchMaxLE(const struct tree *t, int key)
{
    if(t == 0) {
        // no key!
        return INT_MIN;
    } else if(key == t->key) {
        // found it
        return key;
    } else if(key < t->key) {
        // look in left
        return treeSearchMaxLE(t->child[LEFT], key);
    } else {
        // look in right
        int result = treeSearchMaxLE(t->child[RIGHT], key);

        if(result == INT_MIN) {
            // didn't find it
            return t->key;
        } else {
            return result;
        }
    }
}

// rotate the tree pointed to by parent
// so that child in direction moves up
void
treeRotateUp(struct tree **parent, int dir)
{
    // get pointers to anything that might move
    assert(parent);
    struct tree *child = *parent;
    assert(child);
    struct tree *grandchild = child->child[dir];
    assert(grandchild);
    struct tree *middleSubtree = grandchild->child[!dir];

    // do the move
    *parent = grandchild;
    grandchild->child[!dir] = child;
    child->child[dir] = middleSubtree;
}


// insert key into tree pointed to by parent
// if not already present
void
treeInsert(struct tree **parent, int key)
{
    if(*parent == 0) {
        // no key!
        *parent = malloc(sizeof(struct tree));
        (*parent)->key = key;
        (*parent)->heapKey = rand();
        (*parent)->child[LEFT] = (*parent)->child[RIGHT] = 0;
    } else if(key == (*parent)->key) {
        // found it
        return;
    } else if(key < (*parent)->key) {
        // look in left
        treeInsert(&(*parent)->child[LEFT], key);
    } else {
        // look in right
        treeInsert(&(*parent)->child[RIGHT], key);
    }

    // check heap property
    for(int dir = LEFT; dir <= RIGHT; dir++) {
        if((*parent)->child[dir] != 0 && (*parent)->child[dir]->heapKey > (*parent)->heapKey) {
            treeRotateUp(parent, dir);
        }
    }
}

int
main(int argc, char **argv)
{
    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    struct tree *t = 0;
    int key;

    while(scanf("%d", &key) == 1) {
        treeInsert(&t, key);
        treePrint(t);
        printf("--- largest <= 10 is %d\n", treeSearchMaxLE(t, 10));
    }

    treeRotateUp(&t, RIGHT);
    treePrint(t);

    return 0;
}
