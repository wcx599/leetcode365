#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "graph.h"

void
graphPrint(Graph g, FILE *f)
{
    fprintf(f, "digraph {\n");
    for(size_t i = 0; i < g->n; i++) {
        size_t d = g->u[i]->d;
        if(d > 0) {
            fprintf(f, "%zu->{", i);
            for(size_t j = 0; j < d-1; j++) {
                fprintf(f, "%zu,", g->u[i]->v[j]);
            }
            fprintf(f, "%zu}\n", g->u[i]->v[d-1]);
        }
    }
    fprintf(f, "}\n");
}

// Generic graph builder.
// Function degree returns degree of node i.
// Function neighbor returns j-th neighbor of node i.
// Parameter data is passed to both functions.
Graph
graphGenerate(
    size_t n,
    size_t (*degree)(size_t n, size_t i, void *data),
    size_t (*neighbor)(size_t n, size_t i, size_t j, void *data),
    void *data)
{
    Graph g = malloc(sizeof(struct graph) + sizeof(struct neighbors *) * n);
    assert(g);

    g->n = n;

    for(size_t i = 0; i < n; i++) {

        size_t d = degree(n, i, data);
        g->u[i] = malloc(sizeof(struct neighbors) + sizeof(size_t) * d);
        assert(g->u[i]);
        g->u[i]->d = d;

        for(size_t j = 0; j < d; j++) {
            g->u[i]->v[j] = neighbor(n, i, j, data);
        }
    }

    return g;
}

static size_t
degreeFixed(size_t n, size_t i, void *data)
{
    size_t *d = data;
    return *d;
}

static size_t
neighborComplete(size_t n, size_t i, size_t j, void *data)
{
    // we need to be a little careful to skip i
    if(j >= i) {
        return j+1;
    } else {
        return j;
    }
}

Graph
graphComplete(size_t n)
{
    size_t d = n-1;

    return graphGenerate(n, degreeFixed, neighborComplete, &d);
}

static size_t
neighborDirectedCycle(size_t n, size_t i, size_t j, void *data)
{
    return (i+1) % n;
}

Graph
graphDirectedCycle(size_t n)
{
    size_t d = 1;

    return graphGenerate(n, degreeFixed, neighborDirectedCycle, &d);
}

static size_t
binaryTreeNeighbor(size_t n, size_t i, size_t j, void *data)
{
    return 2*i + j + 1;
}

static size_t
binaryTreeDegree(size_t n, size_t i, void *data)
{
    size_t d = 0;
    for(int j = 0; j <= 1; j++) {
        if(binaryTreeNeighbor(n, i, j, data) < n) {
            d++;
        }
    }

    return d;
}

// rooted binary tree based on packed heap
Graph
graphBinaryTree(size_t n)
{
    return graphGenerate(n, 
            binaryTreeDegree,
            binaryTreeNeighbor,
            0);
}

static size_t
hypercubeNeighbor(size_t n, size_t i, size_t j, void *data)
{
    return i^(1 << j);
}

Graph
graphHypercube(size_t n)
{
    size_t logn;

    for(logn = 0; (1<<logn) < n; logn++);

    // bad things will happen if n is not a power of 2
    assert(1 << logn == n);

    return graphGenerate(n, degreeFixed, hypercubeNeighbor, &logn);
}

void
graphDestroy(Graph g)
{
    for(size_t i = 0; i < g->n; i++) {
        free(g->u[i]);
    }
    free(g);
}

static size_t
graphCopyDegree(size_t n, size_t i, void *data)
{
    Graph g2 = data;
    return g2->u[i]->d;
}

static size_t
graphCopyNeighbor(size_t n, size_t i, size_t j, void *data)
{
    Graph g2 = data;
    return g2->u[i]->v[j];
}

Graph
graphCopy(Graph g)
{
    return graphGenerate(g->n, graphCopyDegree, graphCopyNeighbor, g);
}
