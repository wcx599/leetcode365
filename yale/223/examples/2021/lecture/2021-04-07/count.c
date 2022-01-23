#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "counters.h"

// increment a value in a Counters object store in file

#define BASE (10)

int
main(int argc, char **argv)
{

    if(argc != 3) {
        fprintf(stderr, "Usage: %s filename index\n", argv[0]);
        return 1;
    }

    // b means binary file, mostly needed only on  Windows
    FILE *f;
    Counters c;
    
    if((f = fopen(argv[1], "rb")) == 0) {
        // probably doesn't exist yet
        c = countersCreate();
    } else {
        // read existing file
        if((c = countersRead(f)) == 0 || fclose(f) == EOF) {
            perror(argv[1]);
            return 1;
        }
    }

    size_t index = strtoull(argv[2], 0, BASE);

    countersIncrement(c, index);
    printf("%llu\n", countersValue(c, index));

    // write back to argv[1]
    if((f = fopen(argv[1], "wb")) == 0
            || countersWrite(c, f) == 0
            || fclose(f) == EOF) {
        perror(argv[1]);
        return 2;
    }

    countersDestroy(c);

    return 0;
}
