#ifndef _MAPINT_H
#define _MAPINT_H

// dictionary data type mapping strings to ints
// default value is 0
typedef struct mapInt *MapInt;

// non-opaque key type, to be extended by user
typedef struct key {
    const struct methods *methods;
} *Key;

// non-opaque methods type,
// gives list of methods for a key
struct methods {
    void (*destroy)(Key);
    Key (*copy)(Key);
    void (*print)(Key, FILE *);
    int (*isEqual)(Key, Key);
    uint64_t (*hash)(Key);
};

MapInt mapIntCreate(void);
void mapIntDestroy(MapInt);

// returns pointer to matching int location
// this may not remain valid after another
// call to mapIntLookup.
int *mapIntLookup(MapInt, Key);

// print all pairs in table
void mapIntPrint(MapInt, FILE *);

// iterate over all pairs in table, allowing function f
// to operate on them and data
void mapIntForeach(MapInt,
        void (*f)(Key, int *, void *),
        void *data);

#endif
