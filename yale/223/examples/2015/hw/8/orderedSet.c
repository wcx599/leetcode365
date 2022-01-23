#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "orderedSet.h"

/* We'll use a hash table with linear probing.
 * This is not actually ordered, but the only operations that
 * depend on order a linear-time anyway, so we can afford to sort as needed */
struct orderedSet {
    size_t n;     /* number of elements */
    size_t size;  /* size of the table */
    char **table; /* hash table */
};

#define INITIAL_SIZE (16)
#define MAX_ALPHA (0.75)

/* Make a new empty set with given size */
static struct orderedSet *
orderedSetCreateInternal(size_t size)
{
    struct orderedSet *s;

    s = malloc(sizeof(*s));
    assert(s);

    s->n = 0;
    s->size = size;
    s->table = calloc(s->size, sizeof(char *));

    return s;
}

struct orderedSet *
orderedSetCreate(void)
{
    return orderedSetCreateInternal(INITIAL_SIZE);
}

/* Destroy a set */
void 
orderedSetDestroy(struct orderedSet *s)
{
    size_t i;

    for(i = 0; i < s->size; i++) {
        if(s->table[i]) {
            free(s->table[i]);
        }
    }

    free(s->table);
    free(s);
}

/* How many elements in this set? */
size_t 
orderedSetSize(const struct orderedSet *s)
{
    return s->n;
}

static size_t
hash(const char *s)
{
    size_t h;

    /* usual crummy hash function */
    for(h = 0; *s; h = h * 97 + *s++);

    return h;
}

static char *
strMalloc(const char *s)
{
    char *s2;

    s2 = malloc(strlen(s)+1);
    strcpy(s2, s);

    return s2;
}

/* Insert and element without doing size check or malloc */
/* Frees element if already present */
static void
orderedSetInsertInternal(struct orderedSet *s, char *elt)
{
    size_t h;

    assert(elt);

    /* skip over non-empty slots with different values */
    for(h = hash(elt) % s->size; s->table[h] && strcmp(s->table[h], elt); h = (h+1) % s->size);

    /* check if not already present */
    if(s->table[h] == 0) {
        s->table[h] = elt;
        s->n++;
    } else {
        free(elt);
    }
}

/* Insert a new element.  Has no effect if element is already present. */
void 
orderedSetInsert(struct orderedSet *s, const char *elt)
{
    size_t h;
    struct orderedSet *s2;

    if(s->n >= s->size * MAX_ALPHA) {
        /* rebuild the table */
        s2 = orderedSetCreateInternal(s->size * 2);

        /* copy all the elements */
        for(h = 0; h < s->size; h++) {
            if(s->table[h]) {
                orderedSetInsertInternal(s2, s->table[h]);
            }
        }

        /* free the table and then do a brain transplant */
        free(s->table);
        *s = *s2;
        free(s2);
    }

    orderedSetInsertInternal(s, strMalloc(elt));
}

/* Delete an element.  Has no effect if element is not already present. */
void 
orderedSetDelete(struct orderedSet *s, const char *elt)
{
    size_t h;
    char *later;

    /* skip over non-empty slots with different values */
    for(h = hash(elt) % s->size; s->table[h] && strcmp(s->table[h], elt); h = (h+1) % s->size);
    
    /* if we reached a nonempty slot, it must be our target */
    if(s->table[h] != 0) {
        /* remove the initial element */
        free(s->table[h]);
        s->table[h] = 0;
        s->n--;

        /* remove and reinsert any elements up to the next hole, in case they wanted to be earlier */
        for(h = (h+1) % s->size; s->table[h] ; h = (h+1) % s->size) {
            later = s->table[h];
            s->table[h] = 0;
            s->n--;
            orderedSetInsertInternal(s, later);
        }
    }
}

static int
compare(const void *s1, const void *s2)
{
    return strcmp(*((const char **) s1), *((const char **) s2));
}

/* Return a new ordered set containing all elements e
 * for which predicate(arg, x) != 0.
 * The predicate function should be applied to the elements in increasing order. */
struct orderedSet *
orderedSetFilter(const struct orderedSet *s, int (*predicate)(void *arg, const char *), void *arg)
{
    size_t h;
    const char **a;   /* temporary array to sort */
    size_t top;       /* where to put things in a */
    size_t i;
    struct orderedSet *s2;

    a = malloc(sizeof(const char *) * s->size);
    assert(a);
    
    top = 0;

    for(h = 0; h < s->size; h++) {
        if(s->table[h]) {
            a[top++] = s->table[h];
        }
    }

    qsort(a, top, sizeof(const char *), compare);

    s2 = orderedSetCreate();

    for(i = 0; i < top; i++) {
        if(predicate(arg, a[i])) {
            orderedSetInsert(s2, a[i]);
        }
    }

    free(a);

    return s2;
}
