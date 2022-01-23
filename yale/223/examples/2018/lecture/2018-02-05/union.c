#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "eval.h"

union number {
    int asInt;
    double asDouble;
};

/*
#define TYPE_INT (0)
#define TYPE_DOUBLE (1)
*/

enum typeTag {
    TYPE_INT,
    TYPE_DOUBLE
};

struct num {
    int type;   // what kind of thing is this?
    union number value;
};

void
numSetInt(struct num *n, int value)
{
    n->type = TYPE_INT;
    n->value.asInt = value;
}

void
numSetDouble(struct num *n, double value)
{
    n->type = TYPE_DOUBLE;
    n->value.asDouble = value;
}

void
numPrint(const struct num *n)
{
    switch(n->type) {
        case TYPE_INT:
            printf("%d\n", n->value.asInt);
            break;
        case TYPE_DOUBLE:
            printf("%g\n", n->value.asDouble);
            break;
        default:
            printf("Unknown type!\n");
            break;
    }
}


int
main(int argc, char **argv)
{
    union number num;
    struct num n;

    Eval(num.asInt = 17);
    EvalF(g, num.asDouble = 3.141);
    Eval(num.asInt);
    EvalF(g, num.asDouble);

    numSetInt(&n, 17);
    numPrint(&n);
    numSetDouble(&n, 2.718);
    numPrint(&n);

    return 0;
}
