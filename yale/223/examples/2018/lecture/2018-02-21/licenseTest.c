#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "license.h"

#define ACTIVATIONS (5)

int
main(int argc, char **argv)
{
    License *license = licenseCreate(ACTIVATIONS);

    for(int i = 0; i < ACTIVATIONS*2; i++) {
        // license lets me print '.' instead of 'X'
        putchar(licenseActivate(license) ? '.' : 'X');
    }

    putchar('\n');

    licenseDestroy(license);

    return 0;
}
