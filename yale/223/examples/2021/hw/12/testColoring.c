#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "graph.h"

// check a distance-2 coloring given on stdin
// against a graph from file named in argv[1]

int
main(int argc, char **argv)
{
    if(argc != 2) {
        fprintf(stderr, "Usage: %s graph < coloring\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if(f == 0) {
        perror(argv[1]);
        return 1;
    }

    Graph g = graphRead(f);
    assert(g);
    fclose(f);

    size_t n = graphSize(g);
    size_t *coloring = calloc(n, sizeof(size_t));

    for(size_t i = 0; i < n; i++) {
        size_t ii;

        if(scanf("%zu%zu", &ii, &coloring[i]) != 2 || ii != i) {
            fprintf(stderr, "Bad coloring format\n");
            return 2;
        } 
    }

    switch(graphDistance2ColoringCheck(g, coloring)) {

        case COLORING_OUT_OF_RANGE:
            return 3;

        case COLORING_CONFLICT:
            return 4;

        case COLORING_OK:
            puts("Good coloring!");
            break;

        default:
            assert(0);   // case not handled
    }

    free(coloring);
    graphDestroy(g);

    return 0;
}
