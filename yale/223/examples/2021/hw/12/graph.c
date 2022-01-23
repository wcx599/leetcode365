#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "graph.h"

// Graph data structure for computing distance-2 colorings

struct edgeList {
    size_t size;        // amount of slots allocated for neighbors
    size_t degree;      // number of edges; may include duplicates
    size_t neighbors[]; // where the edges go
};

struct graph {
    size_t n;           // number of vertices
    struct edgeList *vertices[];   // adjacency lists
};

#define EDGELIST_INITIAL_SIZE (1)
#define EDGELIST_MULTIPLIER (2)

static struct graph *
graphCreate(size_t n)
{
    struct graph *g = malloc(sizeof(struct graph) + sizeof(struct edgeList) * n);
    assert(g);

    g->n = n;
    
    for(size_t i = 0; i < n; i++) {
        g->vertices[i] = malloc(sizeof(struct edgeList) + sizeof(size_t) * EDGELIST_INITIAL_SIZE);
        assert(g->vertices[i]);

        g->vertices[i]->size = EDGELIST_INITIAL_SIZE;
        g->vertices[i]->degree = 0;
    }

    return g;
}

size_t
graphSize(Graph g)
{
    return g->n;
}

void
graphDestroy(Graph g)
{
    for(size_t i = 0; i < g->n; i++) {
        free(g->vertices[i]);
    }

    free(g);
}

// add edge from u to v
static void
graphAddDirectedEdge(struct graph *g, size_t u, size_t v)
{
    if(g->vertices[u]->degree >= g->vertices[u]->size) {
        g->vertices[u]->size *= EDGELIST_MULTIPLIER;
        g->vertices[u] = 
            realloc(g->vertices[u], 
                sizeof(struct edgeList) 
                + sizeof(size_t) * g->vertices[u]->size);
        assert(g->vertices[u]);
    }

    g->vertices[u]->neighbors[g->vertices[u]->degree++] = v;
}

// add edge from u to v and from v to u
static void
graphAddUndirectedEdge(struct graph *g, size_t u, size_t v)
{
    graphAddDirectedEdge(g, u, v);
    graphAddDirectedEdge(g, v, u);
}

// read a graph from stdin
// returns 0 on error
struct graph *
graphRead(FILE *f)
{
    size_t n;

    if(fscanf(f, "%zu", &n) != 1) {
        return 0;
    }
    // else
    struct graph *g = graphCreate(n);

    size_t u;
    size_t v;

    while(fscanf(f, "%zu%zu", &u, &v) == 2) {
        // we are promised good input but we'll defend
        // against bad just in case
        if(u < 0 || u >= n || v < 0 || v >= n || u == v) {
            graphDestroy(g);
            return 0;
        }

        graphAddUndirectedEdge(g, u, v);
    }

    return g;
}

// compute the maximum degree of a graph
size_t
graphDegree(const struct graph *g)
{
    size_t max = 0;

    for(size_t i = 0; i < g->n; i++) {
        if(g->vertices[i]->degree > max) {
            max = g->vertices[i]->degree;
        }
    }

    return max;
}

#define NO_COLOR (-1)

// Compute a greedy distance-2 coloring of a graph g.
// Return value is pointer to a malloc'd array of
// exactly g->n size_t values.
size_t *
graphDistance2Coloring(Graph g)
{
    size_t *coloring = calloc(g->n, sizeof(size_t));
    assert(coloring);

    for(size_t i = 0; i < g->n; i++) {
        coloring[i] = NO_COLOR;
    }

    // count array will track colors of neighbors of neighbors
    size_t degree = graphDegree(g);
    size_t colors = degree * (degree-1) + 1;
    size_t *count = calloc(colors, sizeof(size_t));

    for(size_t u = 0; u < g->n; u++) {

        // count up all the neighbor-of-neighbor colors
        for(size_t c = 0; c < colors; c++) {
            count[c] = 0;
        }

        for(size_t i = 0; i < g->vertices[u]->degree; i++) {
            size_t v = g->vertices[u]->neighbors[i];
            for(size_t j = 0; j < g->vertices[v]->degree; j++) {
                size_t w = g->vertices[v]->neighbors[j];
                if(coloring[w] != NO_COLOR) {
                    count[coloring[w]]++;
                }
            }
        }

        // pick first unused color
        for(size_t c = 0; c < colors; c++) {
            if(count[c] == 0) {
                coloring[u] = c;
                goto done;
            }
        }
        assert(0);   // ran out of colors!
done:
        ;
    }

    free(count);

    return coloring;
}

// Check an alleged distance 2 coloring
int
graphDistance2ColoringCheck(Graph g, size_t *coloring)
{
    size_t degree = graphDegree(g);
    size_t colors = degree * (degree-1) + 1;
    
    for(size_t u = 0; u < g->n; u++) {
        if(coloring[u] >= colors) {
            fprintf(stderr, "%zu color %zu exceeds %zu\n", u, coloring[u], colors-1);
            return COLORING_OUT_OF_RANGE;
        } 
        // check neighbors of neighbors for conflicts
        for(size_t i = 0; i < g->vertices[u]->degree; i++) {
            size_t v = g->vertices[u]->neighbors[i];
            for(size_t j = 0; j < g->vertices[v]->degree; j++) {
                size_t w = g->vertices[v]->neighbors[j];
                if(u != w && coloring[u] == coloring[w]) {
                    fprintf(stderr, "%zu-%zu-%zu endpoints have same color %zu\n", u, v, w, coloring[u]);
                    return COLORING_CONFLICT;
                }
            }
        }
    }

    return COLORING_OK;
}
