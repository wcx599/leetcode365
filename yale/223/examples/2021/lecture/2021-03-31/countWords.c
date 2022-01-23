#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "mapInt.h"
#include "stringKey.h"
#include "intKey.h"
#include "wordBuffer.h"

// count important words on stdin

static void
printIfOverThreshold(Key key, int *value, void *data)
{
    int threshold = *((int *) data);

    if(*value > threshold) {
        printf("%d ", *value);
        key->methods->print(key, stdout);
        putchar('\n');
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

    MapInt d = mapIntCreate();

    WordBuffer w = wordBufferCreate(stdin);

    const char *word;

    while((word = wordBufferNextWord(w)) != 0) {
        Key k = stringKeyCreate(word);
        (*mapIntLookup(d, k))++;
        k->methods->destroy(k);
    }

    // insert an int key just to show we can
    Key bogus = intKeyCreate(1337);
    *mapIntLookup(d, bogus) = 8192;
    *mapIntLookup(d, bogus) += 8192;
    bogus->methods->destroy(bogus);

    mapIntForeach(d, printIfOverThreshold, &threshold);

    mapIntDestroy(d);
    wordBufferDestroy(w);

    return 0;
}
