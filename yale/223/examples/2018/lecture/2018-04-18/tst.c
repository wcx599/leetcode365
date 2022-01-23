#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tst.h"

#define NUM_KIDS (3)

#define LT (0)
#define EQ (1)
#define GT (2)

struct tst {
    char key;
    struct tst *kids[NUM_KIDS];
};

int
tstContains(const Tst *root, const char *s)
{
    if(root == 0) {
        // empty subtree, go away
        return 0;
    } else if(s[0] < root->key) {
        // it's in the left subtree somewhere
        return tstContains(root->kids[LT], s);
    } else if(s[0] > root->key) {
        // in the right subtree
        return tstContains(root->kids[GT], s);
    } else if(s[0] == '\0') {
        // key is nul, and
        // got to end of string!
        return 1;
    } else {
        // keep looking for rest of chars
        return tstContains(root->kids[EQ], s+1);
    }
}

void 
tstInsert(Tst **parent, const char *s)
{
    if(*parent == 0) {
        // empty subtree, fill it in
        *parent = calloc(1, sizeof(struct tst));
        (*parent)->key = s[0];
    }
    
    if(s[0] < (*parent)->key) {
        // it's in the left subtree somewhere
        tstInsert(&(*parent)->kids[LT], s);
    } else if(s[0] > (*parent)->key) {
        // in the right subtree
        tstInsert(&(*parent)->kids[GT], s);
    } else if(s[0] != '\0') {
        // keep looking for rest of chars
        tstInsert(&(*parent)->kids[EQ], s+1);
    }
}

void
tstDestroy(Tst *root)
{
    if(root) {
        for(int i = LT; i <= GT; i++) {
            tstDestroy(root->kids[i]);
        }
        free(root);
    }
}

// return length of longest string in t
// or 0 if t is empty empty
static size_t
tstMaximumLength(const Tst *t)
{
    if(t == 0) {
        return 0; 
    }
    // else

    size_t max = 0;
    
    for(int i = LT; i <= GT; i ++) {
        size_t kidSize = tstMaximumLength(t->kids[i]);

        // current character counts for EQ if not nul
        if(i == EQ && t->key != '\0') {
            kidSize++;
        }

        if(kidSize > max) {
            max = kidSize;
        }
    }

    return max;
}

// print all strings in t, prepended with first d
// character in buffer.
static void
tstPrintHelper(const Tst *t, char *buffer, size_t d)
{
    if(t){
        // we do the loop in this order even though EQ is a special case
        for(int i = LT; i <= GT; i++) {
            if(i != EQ) {
                // no new characters in buffer
                tstPrintHelper(t->kids[i], buffer, d);
            } else {
                // add current character to buffer
                buffer[d] = t->key;

                if(t->key == '\0') {
                    // end of string, ship it
                    puts(buffer);
                } else {
                    // look for extensions including buffer[d]
                    tstPrintHelper(t->kids[i], buffer, d+1);
                }
            }
        }
    }
}

// print contents of tree in lexicographic order
// this requires a bunch of helper functions to do right.
void 
tstPrint(const Tst *root)
{
    if(root) {
        int len = tstMaximumLength(root);

        char *buffer = malloc(len+1);

        tstPrintHelper(root, buffer, 0);
    }
}

#ifdef TEST_MAIN

int
main(int argc, char **argv)
{
    Tst *t = EMPTY_TST;

    assert(tstMaximumLength(t) == 0);

    tstInsert(&t, "ab");

    assert(tstMaximumLength(t) == 2);

    tstInsert(&t, "abc");
    tstInsert(&t, "abx");
    tstInsert(&t, "ace");
    tstInsert(&t, "ace");

    assert(tstMaximumLength(t) == 3);

    tstInsert(&t, "ability");

    assert(tstMaximumLength(t) == 7);

    assert(tstContains(t, "abc"));
    assert(!tstContains(t, "abd"));

    tstPrint(t);

    tstDestroy(t);

    return 0;
}

#endif
