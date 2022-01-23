#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "stringutil.h"

// Return a malloc'd copy of a string.
// This is probably in the library as strdup,
// but it's not standard, and --pedantic may
// turn it off.
char *
strSave(const char *s)
{
    char *s2 = malloc(strlen(s)+1);  // +1 for the nul
    assert(s2);

    strcpy(s2, s);

    return s2;
}

#define WORD_INITIAL_SIZE (8)

// Fetch the next maximal sequence of alpha chars
// from f, throwing away any preceding non-alpha chars.
// Return value is malloc'd, caller must free.
// Returns null on error or EOF.
char *
getWord(FILE *f)
{
    // A sensible programming language would let us
    // implement an expanding vector once and use
    // it everywhere.
    size_t size = WORD_INITIAL_SIZE;   // bytes allocated for word
    size_t top = 0;
    char *word = malloc(size);
    int c;

    assert(word);

    // eat the non-alphas
    for(;;) {
        c = getchar();
        if(c == EOF) {
            // fail
            free(word);
            return 0;
        } else if(isalpha(c)) {
            // push it back
            ungetc(c, f);
            break;
        }
    }

    // get the alphas
    for(;;) {
        // increase buffer if needed
        if(top >= size) {
            size *= 2;
            word = realloc(word, size);
            assert(word);
        }

        c = getchar();
        if(c == EOF || !isalpha(c)) {
            // end of word!
            ungetc(c, f);
            word[top++] = '\0';
            return word;
        } else {
            word[top++] = c;
        }
    }
}

#ifdef TEST_MAIN

// very minimal test program
int
main(int argc, char **argv)
{
    char *s;
    const char *test = "hello, world";

    s = strSave(test);
    assert(s);
    assert(!strcmp(s,test));
    free(s);

    while((s = getWord(stdin)) != 0) {
        puts(s);
        free(s);
    }

    return 0;
}
#endif
