#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#include "set.h"

/* representation: cast int value to void *, cast it back */
/* this is not actually guaranteed to work */

static size_t 
intHash(void *env, const void *v)
{
    int x;

    x = (int) v;

    return x;
}

static int
intCompare(void *env, const void *v1, const void *v2)
{
    return ((int) v1 - (int) v2);
}

static void *
intCopy(void *env, const void *v)
{
    return (void *) v;
}

static void
intDestroy(void *env, void *v)
{
    /* do nothing */
    ;
}

static struct elementOps intOps = {
    0,
    intHash,
    intCompare,
    intCopy,
    intDestroy
};

/* feed this to setForeach to get max */
static void
computeMaxHelper(void *env, const void *elt)
{
    int *max;
    int e;

    max = env;
    e = (int) elt;

    if(e > *max) {
        *max = e;
    }
}

/* return largest element in set,
 * or INT_MIN if set is empty. */
static int
computeMax(const struct set *s)
{
    int max = INT_MIN;

    setForeach(s, computeMaxHelper, &max);

    return max;
}


static void
printElement(void *env, const void *elt)
{
    printf("%d\n", (int) elt);
}

#define DEFAULT_N (10)

int
main(int argc, char **argv)
{
    struct set *s;
    int i;
    int n;

    if(argc > 1) {
        n = atoi(argv[1]);
    }

    s = setCreate(&intOps);

    assert(computeMax(s) == INT_MIN);

    for(i = 0; i < n; i++) {
        setInsert(s, (void *) i);
    }

    puts("done inserting");

    for(i = 0; i < n; i++) {
        assert(setMember(s, (void *) i));
    }

    puts("done testing membership");

    setDelete(s, (void *) 5);
    assert(!setMember(s, (void *) 5));

    assert(computeMax(s) == n-1);
    setDelete(s, (void *) (n-1));
    assert(computeMax(s) == n-2);

    setForeach(s, printElement, 0);

    setDestroy(s);

    return 0;
}
