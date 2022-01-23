#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "bytes.h"

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    Bytes b = bytesFromString("hi");

    bytesPut(b);

    bytesResize(b, 50);

    strcpy(bytesData(b), "hello there");

    bytesPut(b);
    bytesPut(b);

    bytesDestroy(b);

    return 0;
}
