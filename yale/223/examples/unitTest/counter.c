#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "counter.h"

#include <stdint.h>

#define COUNTER_MAX (UINT64_MAX)

struct counter {
    uint64_t value;
};

/* make a new counter starting at 0 */
Counter *
counterCreate(void)
{
    Counter *c;

    c = malloc(sizeof(Counter));
    assert(c);

    c->value = 0;

    return c;
}

/* destroy a counter */
void
counterDestroy(Counter *c)
{
    free(c);
}

/* return 1 if counter is 0, 0 otherwise */
int 
counterIsZero(const Counter *c)
{
    return c->value == 0;
}

/* increment a counter, returns 1 if successful, 0 if increment would cause overflow */
int
counterIncrement(Counter *c)
{
    if(c->value == COUNTER_MAX) {
        return 0;
    } else {
        c->value++;
        return 1;
    }
}

/* decrement a counter, returns 1 if successful, 0 if decrement would cause underflow */
int
counterDecrement(Counter *c)
{
    if(c->value == 0) {
        return 0;
    } else {
        c->value--;
        return 1;
    }
}

#ifdef TEST_MAIN
int
main(int argc, char **argv)
{
    Counter *c;

    /* black box testing */
    c = counterCreate();                  /* 0 */

    assert(counterIsZero(c));
    assert(counterIncrement(c) == 1);     /* 1 */
    assert(!counterIsZero(c));
    assert(counterIncrement(c) == 1);     /* 2 */
    assert(!counterIsZero(c));
    assert(counterDecrement(c) == 1);     /* 1 */
    assert(!counterIsZero(c));
    assert(counterDecrement(c) == 1);     /* 0 */
    assert(counterIsZero(c));
    assert(counterDecrement(c) == 0);     /* 0 */
    assert(counterIsZero(c));
    assert(counterIncrement(c) == 1);     /* 1 */
    assert(!counterIsZero(c));

    counterDestroy(c);

    /* white box testing */
    c = counterCreate();                  /* 0 */

    assert(c->value == 0);
    assert(counterIncrement(c) == 1);     /* 1 */
    assert(c->value == 1);
    assert(counterIncrement(c) == 1);     /* 2 */
    assert(c->value == 2);
    assert(counterDecrement(c) == 1);     /* 1 */
    assert(c->value == 1);
    assert(counterDecrement(c) == 1);     /* 0 */
    assert(c->value == 0);
    assert(counterDecrement(c) == 0);     /* 0 */
    assert(c->value == 0);
    assert(counterIncrement(c) == 1);     /* 1 */
    assert(c->value == 1);

    /* force counter value to COUNTER_MAX to test for overflow protection */
    c->value = COUNTER_MAX;               /* COUNTER_MAX */
    assert(counterIncrement(c) == 0);     /* COUNTER_MAX */
    assert(c->value == COUNTER_MAX);
    assert(counterDecrement(c) == 1);     /* COUNTER_MAX-1 */
    assert(c->value == COUNTER_MAX-1);
    assert(counterIncrement(c) == 1);     /* COUNTER_MAX */
    assert(c->value == COUNTER_MAX);

    counterDestroy(c);

    return 0;
}
#endif
