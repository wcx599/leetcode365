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
// - Every heapKey in both subtreaps < heapKey.
// heapKeys are chosen randomly to ensure balance with high probability.
struct treap {
    int key;
    int heapKey;
    struct treap *child[NUM_CHILDREN];
};

void
treapDestroy(struct treap **t)
{
    if(*t) {
        for(int dir = LEFT; dir <= RIGHT; dir++) {
            treapDestroy(&(*t)->child[dir]);
        }
    }

    free(*t);
    *t = 0;
}

void
treapPrintHelper(const struct treap *t, int depth)
{
    if(t == 0) {
        return;
    }

    treapPrintHelper(t->child[LEFT], depth+1);

    // print indented root
    for(int i = 0; i < depth; i++) {
        putchar(' ');
    }

    printf("%d [%d]\n", t->key, t->heapKey);

    treapPrintHelper(t->child[RIGHT], depth+1);
}

void
treapPrint(const struct treap *t)
{
    treapPrintHelper(t, 0);
}

// return 1 if it finds key, 0 otherwise
int
treapSearch(const struct treap *t, int key)
{
    if(t == 0) {
        // no key!
        return 0;
    } else if(key == t->key) {
        // found it
        return 1;
    } else if(key < t->key) {
        // look in left
        return treapSearch(t->child[LEFT], key);
    } else {
        // look in right
        return treapSearch(t->child[RIGHT], key);
    }
}

// return largest element <= key
// or INT_MIN if there is no such element.
int
treapSearchMaxLE(const struct treap *t, int key)
{
    if(t == 0) {
        // no key!
        return INT_MIN;
    } else if(key == t->key) {
        // found it
        return key;
    } else if(key < t->key) {
        // look in left
        return treapSearchMaxLE(t->child[LEFT], key);
    } else {
        // look in right
        int result = treapSearchMaxLE(t->child[RIGHT], key);

        if(result == INT_MIN) {
            // didn't find it
            return t->key;
        } else {
            return result;
        }
    }
}

// rotate the treap pointed to by parent
// so that child in direction moves up
void
treapRotateUp(struct treap **parent, int dir)
{
    // get pointers to anything that might move
    assert(parent);
    struct treap *child = *parent;
    assert(child);
    struct treap *grandchild = child->child[dir];
    assert(grandchild);
    struct treap *middleSubtreap = grandchild->child[!dir];

    // do the move
    *parent = grandchild;
    grandchild->child[!dir] = child;
    child->child[dir] = middleSubtreap;
}


// insert key into treap pointed to by parent
// if not already present
void
treapInsert(struct treap **parent, int key)
{
    if(*parent == 0) {
        // no key!
        *parent = malloc(sizeof(struct treap));
        (*parent)->key = key;
        (*parent)->heapKey = rand();
        (*parent)->child[LEFT] = (*parent)->child[RIGHT] = 0;
    } else if(key == (*parent)->key) {
        // found it
        return;
    } else if(key < (*parent)->key) {
        // look in left
        treapInsert(&(*parent)->child[LEFT], key);
    } else {
        // look in right
        treapInsert(&(*parent)->child[RIGHT], key);
    }

    // check heap property
    for(int dir = LEFT; dir <= RIGHT; dir++) {
        if((*parent)->child[dir] != 0 && (*parent)->child[dir]->heapKey > (*parent)->heapKey) {
            treapRotateUp(parent, dir);
        }
    }
}

// delete a node from a treap (if present)
void
treapDelete(struct treap **parent, int key)
{
    // first we look for it
    if(*parent == 0) {
        // not there
        return;
    } else if(key == (*parent)->key) {
        // got it; rotate down until we have a missing kid
        for(;;) {
            // do we have a missing child?
            for(int dir = LEFT; dir <= RIGHT; dir++) {
                if((*parent)->child[dir] == 0) {
                    // yes; free this node and promote other kid
                    struct treap *toDelete = *parent;
                    *parent = toDelete->child[!dir];
                    free(toDelete);
                    return;
                }
            }

            // no missing child, have to rotate down
            int biggerKid;
            if((*parent)->child[LEFT]->heapKey > (*parent)->child[RIGHT]->heapKey) {
                biggerKid = LEFT;
            } else {
                biggerKid = RIGHT;
            }

            // rotate up the bigger kid
            treapRotateUp(parent, biggerKid);

            // node to delete is now on opposite side
            parent = &(*parent)->child[!biggerKid];
        }
    } else {
        treapDelete(&(*parent)->child[key < (*parent)->key ? LEFT : RIGHT], key);
    }
}

#define TEST_THRESHOLD (10)

int
main(int argc, char **argv)
{
    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    struct treap *t = 0;
    int key;

    while(scanf("%d", &key) == 1) {
        if(key >= 0) {
            treapInsert(&t, key);
        } else {
            treapDelete(&t, -key);
        }

        treapPrint(t);
        printf("--- largest <= %d is %d\n", TEST_THRESHOLD, treapSearchMaxLE(t, TEST_THRESHOLD));
    }

    treapDestroy(&t);

    return 0;
}
