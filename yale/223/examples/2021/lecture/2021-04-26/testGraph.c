#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "graph.h"

int
main(int argc, char **argv)
{

    if(argc != 3) {
        fprintf(stderr, "Usage: %s type n\n", argv[0]);
        return 1;
    }

    Graph (*generators[])(size_t) = {
        graphComplete,
        graphDirectedCycle,
        graphBinaryTree,
        graphHypercube
    };

    Graph (*generator)(size_t) = generators[atoi(argv[1])];
    size_t n = strtoull(argv[2], 0, 10);

    Graph g = generator(n);
    Graph g2 = graphCopy(g);

    graphPrint(g2, stdout);

    graphDestroy(g);
    graphDestroy(g2);

    return 0;
}
