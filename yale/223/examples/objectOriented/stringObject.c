#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "stringObject.h"

// wrap strings up as objects
// this extends Object with extra field
struct stringObject {
    struct methods *methods;
    char *string;
};

static void printString(const Object *);
static Object *cloneString(const Object *);
static void destroyString(Object *);

static struct methods stringObjectMethods = {
    cloneString,
    printString,
    destroyString
};

// make a malloc'd copy of s
static char *
strsave(const char *s)
{
    char *s2 = malloc(strlen(s) + 1);
    assert(s2);
    strcpy(s2, s);
    return s2;
}

static void
printString(const Object *self)
{
    fputs(((struct stringObject *) self)->string, stdout);
}

static Object *
cloneString(const Object *self)
{
    return stringObjectCreate(((struct stringObject *) self)->string);
}

static void
destroyString(Object *self)
{
    struct stringObject *sCast = (struct stringObject *) self;
    free(sCast->string);
    free(self);
}

Object *
stringObjectCreate(const char *s)
{
    struct stringObject *self = malloc(sizeof(struct stringObject));
    assert(self);

    self->methods = &stringObjectMethods;
    self->string = strsave(s);

    return (Object *) self;
}

