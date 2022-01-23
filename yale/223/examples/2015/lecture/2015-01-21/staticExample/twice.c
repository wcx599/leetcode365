#include "twice.h"

static int add(int x, int y);

int
twice(int x)
{
    return add(x, x);
}

/* this function is only visible to other function in this file */
static int
add(int x, int y)
{
    return x + y;
}
