#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "set.h"

struct set {
    size_t elementLength;
    size_t size;          /* number of slots */
    size_t count;         /* number of elements */
    struct elt **table;   /* vector of linked list heads */
};

struct elt {
    struct elt *next;
    /* contents go here */
};

#define Contents(e) (((void *) (e)) + sizeof(struct elt))

#define INITIAL_HASH_SIZE (1024)

static Set
setCreateInternal(size_t elementLength, size_t size)
{
    Set s;
    int i;

    s = malloc(sizeof(*s));
    assert(s);

    s->elementLength = elementLength;
    s->size = size;
    s->count = 0;
    s->table = malloc(s->size * sizeof(struct elt *));
    assert(s->table);

    for(i = 0; i < s->size; i++) {
        s->table[i] = 0;
    }

    return s;
}

Set
setCreate(size_t elementLength)
{
    return setCreateInternal(elementLength, INITIAL_HASH_SIZE);
}

static size_t
hash(size_t len, const void *data)
{
    size_t h;
    size_t i;
    const unsigned char *cd;

    h = 0;
    cd = data;

    for(i = 0; i < len; i++) {
        h = h * 97 + cd[i];
    }

    return h;
}

void
setInsert(Set s, const void *elt)
{
    struct elt *e;
    struct elt *next;
    size_t h;
    Set s2;

    if(s->count > s->size) {
        /* rehash */
        s2 = setCreateInternal(s->elementLength, s->size * 2);

        for(h = 0; h < s->size; h++) {
            for(e = s->table[h]; e; e = next) {
                setInsert(s2, Contents(e));
                next = e->next;
                free(e);
            }
        }

        free(s->table);

        *s = *s2;

        free(s2);
    }

    e = malloc(sizeof(struct elt) + s->elementLength);
    assert(e);

    memcpy(Contents(e), elt, s->elementLength);

    h = hash(s->elementLength, elt) % s->size;

    e->next = s->table[h];

    s->table[h] = e;
}

int
setContains(Set s, const void *elt)
{
    size_t h;
    struct elt *e;

    h = hash(s->elementLength, elt) % s->size;

    for(e = s->table[h]; e; e = e->next) {
        if(memcmp(Contents(e), elt, s->elementLength) == 0) {
            return 1;
        }
    }

    return 0;
}

void
setDestroy(Set s)
{
    size_t h;
    struct elt *e;
    struct elt *next;

    for(h = 0; h < s->size; h++) {
        for(e = s->table[h]; e; e = next) {
            next = e->next;
            free(e);
        }
    }
}
