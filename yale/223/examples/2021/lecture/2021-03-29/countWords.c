#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "dictStringInt.h"
#include "wordBuffer.h"

// count important words on stdin

static void
printIfOverThreshold(const char *key, int *value, void *data)
{
    int threshold = *((int *) data);

    if(*value > threshold) {
        printf("%d %s\n", *value, key);
    }
}

int
main(int argc, char **argv)
{

    if(argc != 2) {
        fprintf(stderr, "Usage: %s threshold\n", argv[0]);
        return 1;
    }

    int threshold = atoi(argv[1]);

    DictStringInt d = dictStringIntCreate();

    WordBuffer w = wordBufferCreate(stdin);

    const char *word;

    while((word = wordBufferNextWord(w)) != 0) {
        (*dictStringIntLookup(d, word))++;
    }

    dictStringIntForeach(d, printIfOverThreshold, &threshold);

    dictStringIntDestroy(d);
    wordBufferDestroy(w);

    return 0;
}
