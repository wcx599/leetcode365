#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "license.h"

struct license {
    int limit;  // max activations left (encrypted)
};

#define SECRET (0xdeadbeef)

License *
licenseCreate(int limit)
{
    License *a = malloc(sizeof(License));
    assert(a);

    a->limit = SECRET ^ (1 << limit);

    return a;
}

int
licenseActivate(License *a)
{
    return (a->limit = SECRET ^ ((a->limit ^ SECRET) >> 1)) != SECRET;
}

void
licenseDestroy(License *a)
{
    free(a);
}
