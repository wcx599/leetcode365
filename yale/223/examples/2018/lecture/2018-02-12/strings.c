#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <string.h>

#include "eval.h"

#define Evals(x) EvalF(s, x)

/* my own strcpy */
char *niceStrcpy(char *dest, const char *src)
{
    size_t i; 

    for(i = 0; src[i] != '\0'; i++) {
        dest[i] = src[i];
    }

    dest[i] = '\0';

    return dest;
}

char *uglyStrcpy(char *dest, const char *src)
{
    char *d = dest;

    while( (*d++ = *src++) );

    return dest;
}


int
main(int argc, char **argv)
{
    const char *stringConstant = "hello";

    // this sort of works assuming your text editor and display
    // both encode Unicode as UTF-8, which is backwards-compatible
    // with null-terminated C strings.
    const char *unicodeConstant = "йξقチ☺☹";

    // char bad = '☹'; /* doesn't work, too many bytes in char constant */
    
    char buffer[8];

    Evals(stringConstant);
    Evals(unicodeConstant);

    Evals(strcpy(buffer, stringConstant));
    Evals(buffer);

    Eval(buffer[1] = 'a');
    Evals(buffer);

    Evals(niceStrcpy(buffer, "boo!"));
    Evals(buffer);

    Evals(uglyStrcpy(buffer, "ugly!"));
    Evals(buffer);

    return 0;
}
