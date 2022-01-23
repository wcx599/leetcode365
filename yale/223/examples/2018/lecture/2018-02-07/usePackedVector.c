#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "eval.h"

#include "packedVector.h"  // gets definitions for packed vectors

#define N (10)

int
main(int argc, char **argv)
{
    Vector *v;

    v = vectorCreate(N);

    vectorPrint(v);
    vectorSet(v, 1, 12);
    vectorPrint(v);

    vectorDestroy(v);

    return 0;
}
