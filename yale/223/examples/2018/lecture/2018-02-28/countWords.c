#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hash.h"
#include "stringutil.h"

static void
hashCountHelper(const char *key, int value, void *data)
{
    int *count = data;

    (*count)++;
}

int
hashCount(const Hash *h)
{
    int count = 0;

    hashTraverse(h, hashCountHelper, (void *) &count);

    return count;
}

int
main(int argc, char **argv)
{
    char *word;
    int count;

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    Hash *h = hashCreate(1024);

    while((word = getWord(stdin)) != 0) {
        // set initial count to 0 if not present
        if(!hashGet(h, word, &count)) {
            count = 0;
        }

        count++;

        hashSet(h, word, count);

        free(word);
    }

    // print counts
    hashPrint(h);

    // print total # of unique words 
    printf("%d unique words\n", hashCount(h));

    hashDestroy(h);

    return 0;
}
