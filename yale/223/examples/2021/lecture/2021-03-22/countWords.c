#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "dictStringInt.h"
#include "wordBuffer.h"

// count words on stdin

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    DictStringInt d = dictStringIntCreate();

    WordBuffer w = wordBufferCreate(stdin);

    const char *word;

    while((word = wordBufferNextWord(w)) != 0) {
        (*dictStringIntLookup(d, word))++;
    }

    dictStringIntPrint(d, stdout);

    dictStringIntDestroy(d);
    wordBufferDestroy(w);

    return 0;
}
