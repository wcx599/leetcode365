#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "printFactors.h"

int
main(int argc, char **argv)
{

    if(argc != 2) {
        fprintf(stderr, "Usage: %s numberToFactor\n", argv[0]);
        return 1;
    }
    
    printFactors(atoi(argv[1]));

    return 0;
}
