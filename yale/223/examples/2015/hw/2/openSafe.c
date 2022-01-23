#include <stdlib.h>
#include <assert.h>

#include "safe.h"
#include "openSafe.h"

/* set combination to all zeros */
static void
zeroCombination(int n, int *combination)
{
    int i;

    for(i = 0; i < n; i++) {
        combination[i] = 0;
    }
}

/* non-destructive version of tryCombination */
static int
nondestructiveTryCombination(Safe *s, const int *combination)
{
    int *copy;   /* duplicate of combination */
    int result;  /* result of tryCombination */
    int n;       /* number of tumblers */
    int i;

    n = numTumblers(s);

    copy = (int *) malloc(sizeof(int) * n);

    for(i = 0; i < n; i++) {
        copy[i] = combination[i];
    }

    result = tryCombination(s, copy); 

    free(copy);

    return result;
}

/* update combination to next value */
static void
nextCombination(int n, int base, int *combination)
{
    int i;

    /* we are essentially incrementing an n-digit number in given base */
    /* this means setting any digit that overflows to 0 and continuing */
    /* until we get a digit we can increment without carrying */
    for(i = 0; i < n && ++(combination[i]) >= base; i++) {
        combination[i] = 0;
    }
}


int
openSafe(Safe *s)
{
    int *combination;     /* counter for combinations */
    int n;                /* number of tumblers */
    int base;             /* number of positions */
    int result;           /* result of tryCombination */

    /* allocate space */
    n = numTumblers(s);
    base = numPositions(s);

    combination = malloc(sizeof(int) * n);
    assert(combination);

    for(zeroCombination(n, combination); 
        (result = nondestructiveTryCombination(s, combination)) == SAFE_BAD_COMBINATION;
        nextCombination(n, base, combination));

    free(combination);
    return result;
}
