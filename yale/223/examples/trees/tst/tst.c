#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tst.h"

struct tst_node {
    char key;                   /* value to split on */
    struct tst_node *lt;        /* go here if target[index] < value */
    struct tst_node *eq;        /* go here if target[index] == value */
    struct tst_node *gt;        /* go here if target[index] > value */
};

/* returns 1 if t contains key */
int
tst_contains(TST t, const char *key)
{
    assert(key);

    while(t) {
        if(*key < t->key) {
            t = t->lt;
        } else if(*key > t->key) {
            t = t->gt;
        } else if(*key == '\0') {
            return 1;
        } else {
            t = t->eq;
            key++;
        }
    }

    return 0;
}

/* original recursive insert */
static void
tst_insert_recursive(TST *t, const char *key)
{
    if(*t == 0) {
        *t = malloc(sizeof(**t));
        assert(*t);
        (*t)->key = *key;
        (*t)->lt = (*t)->eq = (*t)->gt = 0;
    }

    /* now follow search */
    if(*key < (*t)->key) {
        tst_insert_recursive(&(*t)->lt, key);
    } else if(*key > (*t)->key) {
        tst_insert_recursive(&(*t)->gt, key);
    } else if(*key == '\0') {
        /* do nothing, we are done */
        ;
    } else {
        tst_insert_recursive(&(*t)->eq, key+1);
    }
}

/* iterative version of above, since somebody asked */
/* This is pretty much standard tail-recursion elimination: */
/* The whole function gets wrapped in a loop, and recursive
 * calls get replaced by assignment */
static void
tst_insert_iterative(TST *t, const char *key)
{
    for(;;) {
        if(*t == 0) {
            *t = malloc(sizeof(**t));
            assert(*t);
            (*t)->key = *key;
            (*t)->lt = (*t)->eq = (*t)->gt = 0;
        }

        /* now follow search */
        if(*key < (*t)->key) {
            t = &(*t)->lt;
        } else if(*key > (*t)->key) {
            t = &(*t)->gt;
        } else if(*key == '\0') {
            /* do nothing, we are done */
            return;
        } else {
            t = &(*t)->eq;
            key++;
        }
    }
}


/* add a new key to a TST */
/* and return the new TST */
TST
tst_insert(TST t, const char *key)
{
    assert(key);

#ifdef USE_RECURSIVE_INSERT
    tst_insert_recursive(&t, key);
#else
    tst_insert_iterative(&t, key);
#endif
    return t;
}

/* free a TST */
void
tst_destroy(TST t)
{
    if(t) {
        tst_destroy(t->lt);
        tst_destroy(t->eq);
        tst_destroy(t->gt);
        free(t);
    }
}
