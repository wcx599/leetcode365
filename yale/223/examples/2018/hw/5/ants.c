#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hash.h"
#include "point.h"
#include "ants.h"

// default active ant
#define INITIAL_ACTIVE (0)

// let's start with something reasonably big
#define INITIAL_HASH_SIZE (1024)

struct ants {
    int active;
    Point ants[NUMBER_OF_ANTS];
    Hash *world;
};

Ants *
antsCreate(void)
{
    Ants *a = malloc(sizeof(Ants));

    a->active = INITIAL_ACTIVE;
    a->world = hashCreate(INITIAL_HASH_SIZE);

    // initialize the ants
    for(int i = 0; i < NUMBER_OF_ANTS; i++) {
        a->ants[i] = PointZero;
    }

    return a;
}

void
antsDestroy(Ants *a)
{
    hashDestroy(a->world);
    free(a);
}

void
antsMove(Ants *a, int operator)
{
    switch(operator) {
        case '.':
            hashSet(a->world, a->ants[a->active], a->active);
            break;
        case '?':
            putchar(hashGet(a->world, a->ants[a->active]));
            break;
        default:
            // try moving active ant
            a->ants[a->active] = pointMove(a->ants[a->active], operator);
            break;
    }
}

void
antsSetActive(Ants *a, int active)
{
    assert(0 <= active && active < NUMBER_OF_ANTS);

    a->active = active;
}

