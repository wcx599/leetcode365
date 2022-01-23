#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "set.h"

struct set {
    size_t size;           // number of slots in table
    size_t n;              // number of elements stored
    char **table;          // table of elements
};

#define INITIAL_SIZE (1024)
#define GROWTH_FACTOR (2)
#define MAX_LOAD_FACTOR (0.75)

// used in setCreate and grow
static Set *
internalCreate(size_t size)
{
    Set *s;

    s = malloc(sizeof(Set));
    s->size = size;
    s->n = 0;
    s->table = malloc(sizeof(char *) * s->size);

    for(size_t i = 0; i < s->size; i++) {
        s->table[i] = 0;
    }

    return s;
}

Set *
setCreate(void)
{
    return internalCreate(INITIAL_SIZE);
}

void
setDestroy(Set *s)
{
    for(size_t i = 0; i < s->size; i++) {
        if(s->table[i]) {
            free(s->table[i]);
        }
    }

    free(s->table);
    free(s);
}

#define MULTIPLIER (97)

static size_t
hash(const char *s)
{
    unsigned const char *us;
    size_t h = 0;

    for(us = (unsigned const char *) s; *us; us++) {
        h = h * MULTIPLIER + *us;
    }

    return h;
}

static void
grow(Set *s)
{
    Set *s2 = internalCreate(s->size * GROWTH_FACTOR);

    for(size_t i = 0; i < s->size; i++) {
        if(s->table[i]) {
            setInsert(s2, s->table[i]);
        }
    }

    // swap guts of s and s2
    Set temp = *s;
    *s = *s2;
    *s2 = temp;

    setDestroy(s2);
}

// should be strdup, but pedantic gcc option turns it off
static char *
strsave(const char *s)
{
    char *s2 = malloc(strlen(s) + 1);
    strcpy(s2, s);
    return s2;
}

void
setInsert(Set *s, const char *key)
{
    // grow table if not enough room
    if(s->n >= s->size * MAX_LOAD_FACTOR) {
        grow(s);
    }

    // look for empty place for new element
    size_t i;
    for(i = hash(key) % s->size; s->table[i] != 0; i = (i+1) % s->size) {
        if(!strcmp(s->table[i], key)) {
            // it's already there
            return;
        }
    }

    // s->table[i] is empty
    s->table[i] = strsave(key);
    s->n++;
}

int
setContains(const Set *s, const char *key)
{
    for(size_t i = hash(key) % s->size; s->table[i] != 0; i = (i+1) % s->size) {
        if(!strcmp(s->table[i], key)) {
            return 1;
        }
    }
    // didn't find it
    return 0;
}

#ifdef TEST_MAIN

int
main(int argc, char **argv)
{
    char buf[4];

    buf[3] = '\0';

    Set *s = setCreate();

    // this is a pretty crummy test but it will detect
    // if we completely screwed up
    for(buf[0] = 'a'; buf[0] <= 'z'; buf[0]++) {
        for(buf[1] = 'a'; buf[1] <= 'z'; buf[1]++) {
            for(buf[2] = 'a'; buf[2] <= 'z'; buf[2]++) {
                assert(!setContains(s, buf));
                setInsert(s, buf);
                assert(setContains(s, buf));
            }
        }
    }

    setDestroy(s);

    return 0;
}
#endif
