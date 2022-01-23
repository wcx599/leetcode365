#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "graph.h"
#include "search.h"

static void
testPrint(Graph g)
{
    graphPrint(g, stdout);
}

// root for testDFS and testBFS
#define DEFAULT_ROOT (0)

// used in testDFS and testBFS
static void
runSearch(Graph g, SearchData (*search)(Graph, Node))
{
    SearchData s = search(g, DEFAULT_ROOT);
    Graph tree = searchTree(g, s);
    graphPrint(tree, stdout);
    graphDestroy(tree);
    searchDataDestroy(s);
}

static void
testDFS(Graph g)
{
    runSearch(g, searchDFS);
}

static void
testBFS(Graph g)
{
    runSearch(g, searchBFS);
}

static Graph
graphCompleteBipartiteEqual(Node n)
{
    return graphCompleteBipartite(n, n);
}

int
main(int argc, char **argv)
{
    int exitCode = 0; // will be set on error

    if(argc != 4) {
        fprintf(stderr, "Usage: %s operation type n\n", argv[0]);
        return 1;
    }

    Graph (*generators[])(Node) = {
        graphComplete,
        graphDirectedCycle,
        graphBinaryTree,
        graphHypercube,
        graphCompleteBipartiteEqual
    };

    struct {
        const char *command;
        void (*handler)(Graph);
    } operation[] = {
        { "print", testPrint },
        { "dfs", testDFS },
        { "bfs", testBFS },
        { 0, 0 }
    };

    Graph (*generator)(Node) = generators[atoi(argv[2])];
    Node n = strtoull(argv[3], 0, 10);

    Graph g = generator(n);

    for(int i = 0; operation[i].command != 0; i++) {
        if(!strcmp(operation[i].command, argv[1])) {
            operation[i].handler(g);
            goto done;
        }
    }

    // command not recognize
    fprintf(stderr, "Bad operation %s\nAllowed operation are:", argv[1]);
    for(int i = 0; operation[i].command != 0; i++) {
        fprintf(stderr, " %s", operation[i].command);
    }
    putc('\n', stderr);
    exitCode = 2;

done:
    graphDestroy(g);

    return exitCode;
}
