#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>

#include "ships.h"

/* basic hash table */
struct field {
    size_t size;         /* number of slots in table */
    size_t occupancy;    /* number of elements in table */
    struct elt **table;  /* hash table, malloc'd */
};

struct elt {
    struct elt *next;   /* pointer to next element in linked list */
    struct ship ship;       /* ship in this element */
};

/* picked more or less at whim from http://planetmath.org/goodhashtableprimes */
#define X_HASH_FACTOR (201326611)
#define Y_HASH_FACTOR (3145739)

static size_t
hash(struct position p)
{
    return X_HASH_FACTOR * p.x + Y_HASH_FACTOR * p.y;
}

#define DEFAULT_INITIAL_SIZE (8)

/* like fieldCreate, but argument gives initial size */
static struct field *
fieldCreateInternal(size_t initialSize)
{
    struct field *f;
    size_t i;

    f = malloc(sizeof(struct field));
    assert(f);

    f->size = initialSize;
    f->occupancy = 0;

    f->table = malloc(sizeof(struct elt *) * f->size);

    for(i = 0; i < f->size; i++) {
        f->table[i] = 0;
    }

    return f;
}

struct field *
fieldCreate(void)
{
    return fieldCreateInternal(DEFAULT_INITIAL_SIZE);
}

/* destroy contents of f but don't free f itself */
static void 
fieldDestroyContents(struct field *f)
{
    size_t i;
    struct elt *e;
    struct elt *next;

    for(i = 0; i < f->size; i++) {
        for(e = f->table[i]; e != 0; e = next) {
            next = e->next;
            free(e);
        }
    }

    free(f->table);
}

void
fieldDestroy(struct field *f)
{
    fieldDestroyContents(f);
    free(f);
}

/* when to grow field */
#define MAX_ALPHA (1)

/*
 * Helper for fieldPlaceShip.
 * 
 * This skips all the sanity-checking in fieldPlaceShip,
 * and just performs the hash table insertion.
 */
static void
fieldInsertShip(struct field *f, struct ship s)
{
    size_t h;     /* hashed coordinates */
    struct elt *e;  /* new element to insert */

    h = hash(s.topLeft) % f->size;

    e = malloc(sizeof(struct elt));
    assert(e);

    e->ship = s;
    e->next = f->table[h];
    f->table[h] = e;
    f->occupancy++;
}


void 
fieldPlaceShip(struct field *f, struct ship s)
{
    struct field *f2;
    struct elt *e;
    struct position pos;
    size_t i;

    /* test if we can just throw this away */
    if(s.name == NO_SHIP_NAME 
            || s.length == 0
            || s.length > MAX_SHIP_LENGTH
            || (s.direction == HORIZONTAL && s.topLeft.x > COORD_MAX - (s.length - 1))
            || (s.direction == VERTICAL   && s.topLeft.y > COORD_MAX - (s.length - 1))
      )
    {
        return;
    }
    /* else */

    if(f->occupancy >= f->size * MAX_ALPHA) {
        /* grow the field */
        f2 = fieldCreateInternal(f->size * 2);

        /* copy to new field */
        for(i = 0; i < f->size; i++) {
            for(e = f->table[i]; e != 0; e = e->next) {
                /* skip testing for occupancy or intersections */
                fieldInsertShip(f2, e->ship);
            }
        }

        /* transplant new field into old field */
        fieldDestroyContents(f);
        *f = *f2;

        free(f2);
    }

    /* check for intersections */
    pos = s.topLeft;
    for(i = 0; i < s.length; i++) {
        if(s.direction == HORIZONTAL) {
            pos.x = s.topLeft.x + i;
        } else {
            pos.y = s.topLeft.y + i;
        } 

        fieldAttack(f, pos);
    }

    /* call helper to do the actual hash table insertion */
    fieldInsertShip(f, s);
}

/*
 * Helper for fieldAttack.
 *
 * If there is a ship with topLeft at given position, return pointer
 * to location in hash table that points to it (either table entry
 * or next component).
 *
 * If not, return null.
 */
static struct elt **
fieldShipAt(struct field *f, struct position p)
{
    struct elt **prev;  /* previous pointer */

    for(prev = &f->table[hash(p) % f->size]; *prev != 0; prev = &((*prev)->next)) {
        if((*prev)->ship.topLeft.x == p.x && (*prev)->ship.topLeft.y == p.y) {
            return prev;
        }
    }

    /* didn't find anything */
    return 0;
}

/*
 * Attack!
 *
 * Drop a shell at given position.
 *
 * Returns 0 if attack misses (does not intersect any ship).
 *
 * Otherwise returns name of ship hit, 
 * which should be freed by caller when no longer needed.
 *
 * Hitting a ship sinks it, removing it from the field.
 */
char
fieldAttack(struct field *f, struct position p)
{
    struct position p2;
    int i;
    int direction;
    struct elt **prev;
    struct elt *freeMe;
    char name;

    for(direction = 0; direction <= 1; direction++) {
        for(i = 0; i < MAX_SHIP_LENGTH && i <= (direction == HORIZONTAL ? p.x : p.y); i++) {
            if(direction == HORIZONTAL) {
                p2.x = p.x - i;
                p2.y = p.y;
            } else {
                p2.x = p.x;
                p2.y = p.y - i;
            }

            prev = fieldShipAt(f, p2);

            if(prev) {
                /* if we sink anybody, it will be this ship */
                /* but maybe it doesn't reach */
                /* or points in the wrong direction */
                if((*prev)->ship.length > i && (*prev)->ship.direction == direction) {
                    /* got it */
                    freeMe = *prev;
                    *prev = freeMe->next;

                    name = freeMe->ship.name;
                    free(freeMe);

                    f->occupancy--;
                    
                    return name;
                } else {
                    /* didn't get it */
                    /* maybe try again in other direction */
                    break;
                }
            }
        }
    }

    /* didn't get anything */
    return NO_SHIP_NAME;
}

/*
 * Return number of ships in the field.
 */
size_t
fieldCountShips(const struct field *f)
{
    return f->occupancy;
}
