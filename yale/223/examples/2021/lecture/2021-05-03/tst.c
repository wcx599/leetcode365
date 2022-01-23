#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "tst.h"

#define NUM_CHILDREN (3)

#define LT (0)
#define EQ (1)
#define GT (2)

struct tst {
    struct tst *child[NUM_CHILDREN];
    char key;
};

int
tstContains(Tst t, const char *s)
{
    while(t != 0) {
        if(s[0] < t->key) {
            t = t->child[LT];
        } else if(s[0] > t->key) {
            t = t->child[GT];
        } else if(s[0] == '\0') {
            // We know that s[0] == t->key, so we win.
            return 1;
        } else {
            // Take the equal branch and advance s.
            t = t->child[EQ];
            s++;
        }
    }

    return 0;
}

void
tstInsert(Tst *t, const char *s)
{
    for(;;) {
        if(*t == 0) {
            // extend TST
            *t = calloc(1, sizeof(struct tst));
            assert(*t);
            (*t)->key = s[0];
            if(s[0] == '\0') {
                // we are done
                return;
            } else {
                t = &((*t)->child[EQ]);
                s++;
            }
        } else if(s[0] < (*t)->key) {
            t = &((*t)->child[LT]);
        } else if(s[0] > (*t)->key) {
            t = &((*t)->child[GT]);
        } else if(s[0] == '\0') {
            // already inserted
            return;
        } else {
            t = &((*t)->child[EQ]);
            s++;
        }
    }
}

// Return the maximum length of any string in t,
// including the final '\0'.
static size_t
tstMaxLength(Tst t)
{
    if(t == 0) {
        return 0;
    }
    // else

    size_t max = 0;

    for(int i = 0; i < NUM_CHILDREN; i++) {
        size_t childLength = tstMaxLength(t->child[i]);

        if(i == EQ) {
            // we add a char crossing into child
            childLength++;
        }

        if(childLength > max) {
            max = childLength;
        }
    }

    return max;
}

// return subtree corresponding to prefix
static 
Tst tstSearchPrefix(Tst t, const char *s)
{
    while(t) {
        if(s[0] == '\0') {
            return t;
        } else if(s[0] < t->key) {
            t = t->child[LT];
        } else if(s[0] > t->key) {
            t = t->child[GT];
        } else {
            t = t->child[EQ];
            s++;
        }
    }

    return 0;
}

static void
tstPrintCompletionsInternal(Tst t, char *buffer, char *next)
{
    if(t) {

        tstPrintCompletionsInternal(t->child[LT], buffer, next);

        *next = t->key;
        if(t->key == '\0') {
            // end of string
            puts(buffer);
        } else {
            tstPrintCompletionsInternal(t->child[EQ], buffer, next+1);
        }

        tstPrintCompletionsInternal(t->child[GT], buffer, next);
    }
}

void
tstPrintCompletions(Tst t, const char *prefix)
{
    size_t lenPrefix = strlen(prefix);
    size_t lenTst = tstMaxLength(t);

    // the +1 avoids some issues if Tst is empty
    char *buffer = malloc(lenPrefix + lenTst + 1);
    assert(buffer);
    strcpy(buffer, prefix);

    Tst subtree = tstSearchPrefix(t, prefix);

    tstPrintCompletionsInternal(subtree, buffer, buffer + lenPrefix);

    free(buffer);
}

static void
tstShowInternal(Tst t, size_t depth)
{
    if(t) {
        tstShowInternal(t->child[LT], depth+1);
        for(size_t i = 0; i < depth; i++) {
            putchar(' ');
        }
        if(isprint(t->key)) {
            printf("%c\n", t->key);
        } else {
            printf("[%02x]\n", t->key);
        }
        tstShowInternal(t->child[EQ], depth+1);
        tstShowInternal(t->child[GT], depth+1);
    }
}

void
tstShow(Tst t)
{
    tstShowInternal(t, 0);
}

void
tstDestroy(Tst t)
{
    if(t) {
        for(int i = LT; i <= GT; i++) {
            tstDestroy(t->child[i]);
        }
        free(t);
    }
}
