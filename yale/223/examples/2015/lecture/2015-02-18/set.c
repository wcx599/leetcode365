#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "set.h"

struct elt {
    struct elt *next;
    int value;
};

struct set {
    size_t size;      /* how many rooms in my hotel? */
    size_t n;         /* how many elements? */
    struct elt **head; /* array of linked list heads */
};

#define DEFAULT_SIZE (16)

/* make a new set */
static struct set *
setCreateInternal(size_t initialSize)
{
    struct set *s;
    size_t i;

    s = malloc(sizeof(struct set));
    s->size = initialSize;
    s->n = 0;

    s->head = malloc(sizeof(struct elt *) * s->size);

    for(i = 0; i < s->size; i++) {
        s->head[i] = 0;
    }

    return s;
}

struct set *
setCreate(void)
{
    return setCreateInternal(DEFAULT_SIZE);
}

/* free up space used by set */
void setDestroy(struct set *s)
{
    size_t h;
    struct elt *freeMe;

    for(h = 0; h < s->size; h++) {
        while(s->head[h]) {
            freeMe = s->head[h];
            s->head[h] = freeMe->next;
            free(freeMe);
        }
    }

    free(s->head);
    free(s);
}

/* compute random-looking hash of x */
static size_t
hash(size_t range, int x)
{
    return (97 * x) % range;
}

static void
expand(struct set *s)
{
    struct set *s2;
    struct set swap;  /* holds contents of s temporarily for swap */
    size_t h;
    struct elt *e;

    s2 = setCreateInternal(s->size * 2);

    printf("Expanding to %zu\n", s2->size);

    /* move everything from s to s2 */
    for(h = 0; h < s->size; h++) {
        for(e = s->head[h]; e != 0; e = e->next) {
            setInsert(s2, e->value);
        }
    }

    swap = *s;
    *s = *s2;   /* put new hash table in old struct */
    *s2 = swap;

    setDestroy(s2);
}

/* add x to set */
void
setInsert(struct set *s, int x)
{
    struct elt *e;
    size_t h;

    if(setMember(s, x)) {
        /* we already have a copy */
        return;
    }
    /* else */

    if(s->n >= s->size) {
        /* make the hash table bigger */
        expand(s);
    }

    e = malloc(sizeof(struct elt));

    h = hash(s->size, x);

    e->next = s->head[h];
    s->head[h] = e;
    e->value = x;

    s->n++;
}

/* remove x from set */
void 
setDelete(struct set *s, int x)
{
    /*
     * Sneaky trick: instead of keeping a pointer to an elt
     * as we walk through the list, we keep a pointer to the
     * location in the list that points to it.  That way, when
     * we decide to patch out *e, we have the location (e) that
     * we need to change to point to (*e)->next.
     */
    struct elt **e;
    struct elt *freeMe;

    for(e = &s->head[hash(s->size, x)]; *e != 0; e = &((*e)->next)) {
        if((*e)->value == x) {
            /* got it */
            freeMe = *e;
            *e = freeMe ->next;
            free(freeMe);

            /* since we check on insert that we have no duplicates, we are done */
            break;
        }
    }
}

/* test membership, return true if x is in set */
int 
setMember(const struct set *s, int x)
{
    struct elt *e;

    for(e = s->head[hash(s->size, x)]; e != 0; e = e->next) {
        if(e->value == x) {
            return 1;
        }
    }

    return 0;
}
