#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "stack.h"

#define N (3)

// wrap strings up as objects
// this extends struct object with extra field
struct stringObject {
    struct methods *methods;
    char *string;
};

static void printString(const struct object *s);
static struct object *cloneString(const struct object *s);
static void destroyString(struct object *s);

static struct methods stringObjectMethods = {
    cloneString,
    printString,
    destroyString
};

static void
printString(const struct object *s)
{
    fputs(((struct stringObject *) s)->string, stdout);
}

static struct object *
cloneString(const struct object *s)
{
    struct stringObject *s2 = malloc(sizeof(struct stringObject));
    struct stringObject *sCast = (struct stringObject *) s;

    s2->methods = &stringObjectMethods;
    s2->string = malloc(strlen(sCast->string) + 1);
    strcpy(s2->string, sCast->string);

    return (struct object *) s2;
}

static void
destroyString(struct object *s)
{
    struct stringObject *sCast = (struct stringObject *) s;
    free(sCast->string);
    free(s);
}

// same thing but for ints
// this extends struct object with extra field
struct intObject {
    struct methods *methods;
    int value;
};

static void printInt(const struct object *s);
static struct object *cloneInt(const struct object *s);
static void destroyInt(struct object *s);

static struct methods intObjectMethods = {
    cloneInt,
    printInt,
    destroyInt
};

static void
printInt(const struct object *s)
{
    printf("%d", ((struct intObject *) s)->value);
}

static struct object *
cloneInt(const struct object *s)
{
    struct intObject *s2 = malloc(sizeof(struct intObject));

    // just copy over the fields
    *s2 = *((struct intObject *) s);

    return (struct object *) s2;
}

static void
destroyInt(struct object *s)
{
    // we don't have any pointers, so we can just free the block
    free(s);
}

// do some stack stuff
int
main(int argc, char **argv)
{
    char str[] = "hi";
    struct object *ret;
    struct stringObject so = { &stringObjectMethods, str };
    struct intObject io = { &intObjectMethods, 0 };

    int n = N;
    if(argc >= 2) {
        n = atoi(argv[1]);
    }

    Stack *s = stackCreate();

    for(int i = 0; i < n; i++) {
        str[0] = 'a' + i;
        stackPush(s, (struct object *) &so);
        stackPrint(s);
        io.value = i;
        stackPush(s, (struct object *) &io);
        stackPrint(s);
    }

    while(stackNotEmpty(s)) {
        ret = stackPop(s);
        putchar('[');
        ret->methods->print(ret);
        ret->methods->destroy(ret);
        fputs("] ", stdout);
        stackPrint(s);
    }

    stackDestroy(s);

    return 0;
}
