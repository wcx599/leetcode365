#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "set.h"

static int
isVowel(int c)
{
    switch(c) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return 1;
        default:
            return 0;
    }
}

#define MAX_CLOSE_DISTANCE (5)

static int
isClose(int c1, int c2)
{
    return abs(c1-c2) <= MAX_CLOSE_DISTANCE;
}

static int
isMatch(int c1, int c2)
{
    return isClose(c1, c2) || (isVowel(c1) && isVowel(c2));
}

// used for history linked list
struct history {
    char *word;
    const struct history *prev;
};

static void
printHistory(const struct history *current)
{
    if(current) {
        printHistory(current->prev);
        puts(current->word);
    }
}

#define LONG_OFFSET (3)

// attempts to shrink prev->word to one character
// if it works, prints sequence of intermediate words
// and returns 1, else returns 0.
static int
shrink(Set *found, const struct history *prev)
{
    size_t n = strlen(prev->word);

    if(n <= 1) {
        // we are done
        printHistory(prev);
        return 1;
    } else if(setContains(found, prev->word)) {
        // dead end
        return 0;
    } else {
        // mark as previously found
        setInsert(found, prev->word);

        // try all reductions
        struct history current;
        current.prev = prev;
        current.word = malloc(n);

        // start with the short-offset reductions
        for(size_t i = 0; i+1 < n; i++) {
            if(isMatch(prev->word[i], prev->word[i+1])) {
                // shrink and recurse
                strncpy(current.word, prev->word, i);
                strcpy(current.word + i, prev->word + i + 1);

                if(shrink(found, &current)) {
                    // got it
                    free(current.word);
                    return 1;
                }
            }
        }

        // now the long-offset ones
        for(size_t i = 0; i + LONG_OFFSET < n; i++) {
            if(isMatch(prev->word[i], prev->word[i+LONG_OFFSET])) {
                // shrink and recurse
                strncpy(current.word, prev->word, i);
                current.word[i] = prev->word[i+LONG_OFFSET];
                strncpy(current.word + i + 1, prev->word + i + 1, LONG_OFFSET - 1);
                strcpy(current.word + i + LONG_OFFSET, prev->word + i + LONG_OFFSET + 1);

                if(shrink(found, &current)) {
                    // got it
                    free(current.word);
                    return 1;
                }
            }
        }

        // found nothing
        free(current.word);
        return 0;
    }
}

int
main(int argc, char **argv)
{

    if(argc != 2) {
        fprintf(stderr, "Usage: %s word\n", argv[0]);
        return 1;
    }

    struct history current;
    current.prev = 0;
    current.word = argv[1];

    Set *s = setCreate();

    shrink(s, &current);

    setDestroy(s);

    return 0;
}
