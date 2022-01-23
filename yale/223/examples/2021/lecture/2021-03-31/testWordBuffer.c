#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "wordBuffer.h"

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    WordBuffer w = wordBufferCreate(stdin);

    const char *s;

    while((s = wordBufferNextWord(w)) != 0) {
        puts(s);
    }

    wordBufferDestroy(w);

    return 0;
}
