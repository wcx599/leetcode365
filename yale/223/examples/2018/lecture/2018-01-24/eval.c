#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>   /* for CHAR_BITS */

#include "eval.h"     /* Eval and EvalF macros */

int
die(void)
{
    puts("AAARGGHGGH!!!!");
    abort();

    return 0;
}

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    Eval(! 27);
    Eval(! 0);
    Eval(!! 27); // don't do this

    Eval(3 && 4);
    Eval(0 && 4);
    Eval(3 || 4);
    Eval(0 || 4);

    Eval(0 && die());
    Eval(1 || die());

    // Eval(die());

    int x;

    Eval( (x=3, x+1) );
    Eval(x);
    Eval( (x=3, x += 1) );
    Eval(x);

    int i;
    int iSquared;

    for(i = 0, iSquared = 0; i < 6; i++, iSquared += i+i-1) {
        printf("%d %d\n", i, iSquared);
    }

    // Eval(2 & 3 == 2);
     Eval((2 & 3) == 2);

    return 0;
}
