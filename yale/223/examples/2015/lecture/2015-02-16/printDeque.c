#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "deque.h"

/* print content of deque to file */
/* does horrible things to dConst, but it's morally const */
void
dequePrint(const struct deque *dConst, FILE *f)
{
    struct deque *d;   /* non-const copy of dConst pointer */
    struct deque *d2;  /* temporary storage for stuff we already printed */
    int value;

    d = (struct deque *) dConst;
    d2 = dequeCreate();

    assert(d2);

    /* print everything out */
    while(!dequeIsEmpty(d)) {
        value = dequePop(d, DEQUE_FRONT);
        dequePush(d2, DEQUE_BACK, value);

        fprintf(f, "%d ", value);
    }

    putc('\n', f);

    /* put it back */
    while(!dequeIsEmpty(d2)) {
        value = dequePop(d2, DEQUE_FRONT);
        dequePush(d, DEQUE_BACK, value);
    }
}

int
main(int argc, char **argv)
{
    int i;
    struct deque *d;

    d = dequeCreate();

    for(i = 0; i < 10; i++) {
        dequePush(d, i % 2, i);
        dequePrint(d, stdout);
    }

    for(i = 0; i < 10; i++) {
        dequePop(d, i % 2);
        dequePrint(d, stdout);
    }

    dequeDestroy(d);

    return 0;
}


        
