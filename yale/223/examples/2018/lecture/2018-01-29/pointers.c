#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "eval.h"

int Global = 'z';

/* pointers let us return multiple values */
/* compute sum and product of two ints */
void
sumAndProduct(int x, int y, int *sum, int *product)
{
    *sum = x+y;
    *product = x*y;
}

int
main(int argc, char **argv)
{
    int x = 1;
    int y = 2;
    int z = 3;
    int s;
    int prod;
    int *p;

    p = &x;

    printf("%p\n", (void *) p);

    EvalF(p, (void *) &x);
    EvalF(p, (void *) &y);
    EvalF(p, (void *) &z);

    EvalF(p, (void *) &Global);

    EvalF(p, (void *) &main);

    p = &Global;
    Eval(*p = 12);
    Eval(Global);

    sumAndProduct(x, y, &s, &prod);
    Eval(s);
    Eval(prod);

    Eval(&x == p);

    Eval(y);
    Eval(*(&x + 1));  // EVIL
    Eval(*(&x + 2));  // EVIL
    Eval(*(&x + 7));  // EVIL
    Eval(*(&x + (1<<20)));  // EVIL

    return 0;
}
