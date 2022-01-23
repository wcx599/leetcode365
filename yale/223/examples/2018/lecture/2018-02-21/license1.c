#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "license.h"

struct license {
    int limit;  // max activations
    int used;   // how many activations used
};

License *
licenseCreate(int limit)
{
    License *a = malloc(sizeof(License));
    assert(a);

    a->limit = limit;
    a->used = 0;

    return a;
}

int
licenseActivate(License *a)
{
    return a->used++ < a->limit;
}

void
licenseDestroy(License *a)
{
    free(a);
}
