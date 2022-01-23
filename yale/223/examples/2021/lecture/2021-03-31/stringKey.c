#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "mapInt.h"
#include "stringKey.h"

struct stringKey {
    struct key inherited;
    char data[];
};

static void
destroy(Key self)
{
    free(self);
}

static Key
copy(Key self)
{
    return stringKeyCreate(((StringKey) self)->data);
}

static void
print(Key self, FILE *f)
{
    fputs(((StringKey) self)->data, f);
}

static int
isEqual(Key self, Key other)
{
    if(self->methods != other->methods) {
        return 0;
    } else {
        StringKey me = (StringKey) self;
        StringKey you = (StringKey) other;

        return strcmp(me->data, you->data) == 0;
    }
}

#define FNV_PRIME_64 ((1ULL<<40)+(1<<8)+0xb3)
#define FNV_OFFSET_BASIS_64 (14695981039346656037ULL)

static uint64_t
FNV1a(const char *s)
{
    uint64_t h = FNV_OFFSET_BASIS_64;

    while(*s != '\0') {
        h ^= *s++;
        h *= FNV_PRIME_64;
    }

    return h;
}

static uint64_t
hash(Key self)
{
    return FNV1a(((StringKey) self)->data);
}

static const struct methods StringKeyMethods = {
    destroy,
    copy,
    print,
    isEqual,
    hash
};

Key
stringKeyCreate(const char *s)
{
    StringKey k = malloc(sizeof(struct stringKey) + strlen(s) + 1);
    assert(k);
    strcpy(k->data, s);
    k->inherited.methods = &StringKeyMethods;

    return (Key) k;
}

