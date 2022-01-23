#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "mapInt.h"
#include "intKey.h"

struct intKey {
    struct key inherited;
    int data;
};

static void
destroy(Key self)
{
    free(self);
}

static Key
copy(Key self)
{
    return intKeyCreate(((intKey) self)->data);
}

static void
print(Key self, FILE *f)
{
    fprintf(f, "%d", ((intKey) self)->data);
}

static int
isEqual(Key self, Key other)
{
    if(self->methods != other->methods) {
        return 0;
    } else {
        intKey me = (intKey) self;
        intKey you = (intKey) other;

        return me->data == you->data;
    }
}

#define FNV_PRIME_64 ((1ULL<<40)+(1<<8)+0xb3)
#define FNV_OFFSET_BASIS_64 (14695981039346656037ULL)

static uint64_t
intFNV1a(int x)
{
    uint64_t h = FNV_OFFSET_BASIS_64;

    char *s = (char *) &x;

    for(int i = 0; i < sizeof(int); i++) {
        h ^= s[i];
        h *= FNV_PRIME_64;
    }

    return h;
}

static uint64_t
hash(Key self)
{
    return intFNV1a(((intKey) self)->data);
}

static const struct methods intKeyMethods = {
    destroy,
    copy,
    print,
    isEqual,
    hash
};

Key
intKeyCreate(int value)
{
    intKey k = malloc(sizeof(struct intKey));
    assert(k);
    k->data = value;
    k->inherited.methods = &intKeyMethods;

    return (Key) k;
}

