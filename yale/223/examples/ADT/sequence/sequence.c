#include <stdlib.h>

#include "sequence.h"

struct sequence {
    int next;   /* next value to return */
    int step;   /* how much to increment next by */
};

Sequence
seq_create(int init)
{
    return seq_create_step(init, 1);
}

Sequence
seq_create_step(int init, int step)
{
    Sequence s;

    s = malloc(sizeof(*s));
    if(s == 0) return 0;
    s->next = init;
    s->step = step;
    return s;
}

void
seq_destroy(Sequence s)
{
    free(s);
}

int
seq_next(Sequence s)
{
    int ret;            /* saves the old value before we increment it */

    ret = s->next;
    s->next += s->step;

    return ret;
}
