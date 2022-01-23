#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "hash.h"

// invariant: empty slots have used = 1
struct elt {
    int used;
    Point key;
    int value;
};

struct hash {
    size_t size;   // size of array
    size_t elts;   // how many elements
    struct elt *a; // actual table of elements
};

#define MULTIPLIER (2)   // extra space to keep load factor down, see hashCreate
#define MINIMUM_SIZE (4) // avoid trouble if user asks for 0 or something

// create a hash table for storing up to n elts
Hash *
hashCreate(size_t n) {
    Hash *h = malloc(sizeof(struct hash));

    if(n < MINIMUM_SIZE) {
        n = MINIMUM_SIZE;
    }
    
    h->size = n;
    h->elts = 0;

    h->a = calloc(h->size, sizeof(struct elt));

    return h;
}

void
hashDestroy(Hash *h)
{
    // don't need to free anything but the table itself
    // since keys are all stored in a.
    free(h->a);
    free(h);
}

// some large prime
#define HASH_MULTIPLIER (9617489411)

// terrible hash function
static size_t
hashFunction(Point p)
{
    size_t h = 0;

    for(int i = 0; i < POINT_DIMENSION; i++) {
        h = h * HASH_MULTIPLIER + p.coords[i];
    }

    return h;
}

// test if two points are equal
static int
pointsEqual(Point x, Point y)
{
    for(int i = 0; i < POINT_DIMENSION; i++) {
        if(x.coords[i] != y.coords[i]) {
            return 0;
        }
    }
    // else
    return 1;
}

// find position of key in h
// or first empty position if not in h
static size_t
hashFind(const Hash *h, Point key)
{
    size_t i = hashFunction(key) % h->size;

    while(h->a[i].used != 0 && !pointsEqual(h->a[i].key, key)) {
        i = (i + 1) % h->size;
    }

    return i;
}

void
hashSet(Hash *h, Point key, int value)
{
    // where should key go?
    size_t pos = hashFind(h, key);

    if(h->a[pos].used == 0) {
        // put in key and value
        h->a[pos].used = 1;
        h->a[pos].key = key;
        h->a[pos].value = value;
        h->elts++;

        if(h->elts * MULTIPLIER > h->size) {
            // grow the table
            Hash *h2 = hashCreate(h->size * MULTIPLIER);

            // insert all the elts into the new table
            for(size_t i = 0; i < h->size; i++) {
                if(h->a[i].used) {
                    hashSet(h2, h->a[i].key, h->a[i].value);
                }
            }

            // free the guts of the old table
            free(h->a);

            // transplant the fields of the new table to the old table
            *h = *h2;

            // free the new table
            free(h2);
        }
    } else {
        // just update in place
        h->a[pos].value = value;
    }
}

// if key is in h, return value
// else return HASH_DEFAULT
int 
hashGet(const Hash *h, Point key)
{
    size_t pos = hashFind(h, key);

    if(h->a[pos].used == 0) {
        return HASH_DEFAULT;
    } else {
        return h->a[pos].value;
    }
}

// print contents of h
void
hashPrint(const Hash *h) {
    for(size_t i = 0; i < h->size; i++) {
        if(h->a[i].used != 0) {
            for(int j = 0; j < POINT_DIMENSION; j++) {
                printf("%d ", h->a[i].key.coords[j]);
            }
            printf("%x\n", h->a[i].value);
        }
    }
}

#ifdef TEST_MAIN

#define HASH_SIZE (4)


// Set all points with first i coords in p
// and last POINT_DIMENSION - i coords in 0..n-1
// to value returned by f.
static void
hashFill(Hash *h, Point p, int i, int n, int (*f)(Point))
{
    if(i == POINT_DIMENSION) {
        hashSet(h, p, f(p));
        // test value immediately
        assert(hashGet(h, p) == f(p));
    } else {
        for(int j = 0; j < n; j++) {
            p.coords[i] = j;
            hashFill(h, p, i+1, n, f);
        }
    }
}

// check if all points as in hashFill
// have right value
static void
hashTestFill(const Hash *h, Point p, int i, int n, int (*f)(Point))
{
    if(i == POINT_DIMENSION) {
        assert(hashGet(h, p) == f(p));
    } else {
        for(int j = 0; j < n; j++) {
            p.coords[i] = j;
            hashTestFill(h, p, i+1, n, f);
        }
    }
}

// some fill functions
static int
pointSum(Point p)
{
    int sum = 0;

    for(int i = 0; i < POINT_DIMENSION; i++) {
        sum += p.coords[i];
    }

    return sum;
}

static int
pointDefault(Point p)
{
    return HASH_DEFAULT;
}

int
main(int argc, char **argv)
{
    Point p;

    int n = atoi(argv[1]);

    Hash *h = hashCreate(HASH_SIZE);
    assert(h);

    hashTestFill(h, p, 0, n, pointDefault);

    hashFill(h, p, 0, n, pointSum);
    hashTestFill(h, p, 0, n, pointSum);

    hashFill(h, p, 0, n, pointDefault);
    hashTestFill(h, p, 0, n, pointDefault);

    hashDestroy(h);

    return 0;
}
#endif
