#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "eval.h"

char *
myStrcat(char *dst, const char *src)
{
    strcpy(dst + strlen(dst), src);
    return dst;
}

char *
myStrcpy(char *dst, const char *src)
{
    // +1 for the null character
    memcpy(dst, src, strlen(src) + 1);
    return dst;
}

int
main(int argc, char **argv)
{
    char buffer[1024];

    EvalF(zu, strlen("abc"));

    EvalF(s, strcpy(buffer, "abcd"));
    EvalF(s, strcat(buffer, "efg"));
    EvalF(s, myStrcat(buffer, "-efg"));
    EvalF(zu, strlen(buffer));

    // testing if two strings are equal
    Eval(!strcmp("abc", "abc"));
    Eval(!strcmp("abc", "abcd"));
    

    // ordering of strings
    Eval(strcmp("abc", "def"));
    Eval(strcmp("abc", "abcd"));

    // using memcpy
    EvalF(s, myStrcpy(buffer, "hello world"));



    return 0;
}
