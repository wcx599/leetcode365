#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "ants.h"

int
main(int argc, char **argv)
{
    int c;
    Ants *a;

    a = antsCreate();

    // outer loop cycles through ants
    for(;;) {
        if((c = getchar()) == EOF) {
            // we are done
            goto done;
        }
        // else
        antsSetActive(a, c);

        for(;;) {
            switch(c = getchar()) {
                case '\n':
                    goto nextAnt;
                case EOF:
                    // we are done
                    goto done;
                default:
                    // give it to the ants
                    antsMove(a, c);
                    break;
            }
        }
nextAnt:
        // escape from inner loop
        ;
    }
done:
    // escape from both loops
    antsDestroy(a);

    return 0;
}
