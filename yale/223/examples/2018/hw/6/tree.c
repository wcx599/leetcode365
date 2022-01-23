#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "tree.h"

// invariant: kids non-null if n > 0
// but may have non-null kids even if n == 0
// if kids is non-null, it is malloc'd data
struct tree {
    int size;    // size of subtree rooted here
    size_t n;      // number of kids
    Tree **kids;   // array of pointers to kids if n > 0
};

void
treeWrite(const Tree *t, FILE *f)
{
    putc('[', f);
    for(int i = 0; i < t->n; i++) {
        treeWrite(t->kids[i], f);
    }
    putc(']', f);
}

#define INITIAL_KIDS_SIZE (4)

// in case we ever change the format
#define TREE_START ('[')
#define TREE_END   (']')

// returns null if can't read tree
Tree *
treeRead(FILE *f)
{
    int c;
    Tree *t;
    size_t kidsSize;  // how many slots we allocated

    // if we don't start with '[', return null
    if((c = getc(f)) != TREE_START) {
        ungetc(c, f);
        return 0;
    }

    t = malloc(sizeof(Tree));
    t->size = 1;
    t->n = 0;

    // we'll allocate space for some kids an prune later
    kidsSize = INITIAL_KIDS_SIZE;
    t->kids = malloc(kidsSize * sizeof(Tree *));

    while((t->kids[t->n] = treeRead(f)) != 0) {
        // we just got another kid
        t->size += t->kids[t->n]->size;
        t->n++;

        if(t->n == kidsSize) {
            kidsSize *= 2;
            t->kids = realloc(t->kids, kidsSize * sizeof(Tree *));
        }
    }

    // ran out of kids, is next char TREE_END?
    if((c = getc(f)) != TREE_END) {
        ungetc(c, f);  // this will make parent fail as well
        treeDestroy(t);
        return 0;
    }

    // everything is good, clean up
    if(t->n == 0) {
        free(t->kids);
        t->kids = 0;
    } else {
        t->kids = realloc(t->kids, t->n * sizeof(Tree *));
    }

    return t;
}

void
treeDestroy(Tree *t)
{
    if(t->kids) {
        for(size_t i = 0; i < t->n; i++) {
            treeDestroy(t->kids[i]);
        }
        free(t->kids);
    }

    free(t);
}

// helper for qsort
static int
treeCompare(const void *a, const void *b)
{
    return (*((Tree **) b))->size - (*((Tree **) a))->size;
}

void
treeSort(Tree *t)
{
    if(t->n > 0) {
        qsort((void *) t->kids, t->n, sizeof(Tree *), treeCompare);

        for(int i = 0; i < t->n; i++) {
            treeSort(t->kids[i]);
        }
    }
}
