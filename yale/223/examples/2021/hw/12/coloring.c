#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

// Compute a distance-2 coloring on a given undirected graph.
//
// Input format is
//
// <number of nodes>
// <u1> <v1>
// <u2> <v2>
// ...
//
// Where <number of nodes>, <ui>, etc. are all %d-formatted ints,
// edges are ui-vi in no particular order.
//
// Output is list of nodes with matching colors in {0..k-1}.

#include "graph.h"

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s < graph\n", argv[0]);
        return 1;
    }

    Graph g = graphRead(stdin);
    assert(g);

    size_t *coloring = graphDistance2Coloring(g);

    size_t n = graphSize(g);
    for(size_t i = 0; i < n; i++) {
        printf("%zu %zu\n", i, coloring[i]);
    }

    free(coloring);
    graphDestroy(g);

    return 0;
}
