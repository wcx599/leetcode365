#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "tst.h"

int
main(int argc, char **argv)
{
    char *word;
    Tst t = TST_EMPTY;

    while(scanf("%ms", &word) == 1) {
        tstInsert(&t, word);
        free(word);
    }

    if(argc == 1) {
        tstShow(t);
    } else {
        for(int i = 1; i < argc; i++) {
            printf("=== Completions of \"%s\"\n", argv[i]);
            tstPrintCompletions(t, argv[i]);
        }
    }

    tstDestroy(t);

    return 0;
}
