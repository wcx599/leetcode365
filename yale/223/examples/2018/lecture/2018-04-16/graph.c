#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "graph.h"

// adjacency list element
struct elt {
    struct elt *next;
    Vertex v;
};

struct graph {
    Vertex n;   // # of vertices
    size_t edgeCount;  // # of edges
    struct elt **alist;
};

Graph *
graphCreate(Vertex n)
{
    Graph *g = malloc(sizeof(Graph));
    g->n = n;
    g->edgeCount = 0;
    g->alist = calloc(n, sizeof(struct elt *));

    return g;
}

void
graphAddEdge(Graph *g, Vertex u, Vertex v)
{
    struct elt *e = malloc(sizeof(struct elt));
    e->v = v;
    e->next = g->alist[u];
    g->alist[u] = e;
    g->edgeCount++;
}

void
graphDestroy(Graph *g)
{
    for(Vertex u = 0; u < g->n; u++) {
        while(g->alist[u]) {
            struct elt *next = g->alist[u]->next;
            free(g->alist[u]);
            g->alist[u] = next;
        }
    }

    free(g->alist);
    free(g);
}

Vertex
graphSize(const Graph *g)
{
    return g->n;
}

size_t
graphEdgeCount(const Graph *g)
{
    return g->edgeCount;
}

// print a graph to file in GraphViz input format
void
graphPrint(const Graph *g, FILE *file)
{
    Vertex n = graphSize(g);

    puts("digraph G {\nrankdir=LR");

    for(Vertex u = 0; u < n; u++) {
        for(struct elt *e = g->alist[u]; e != 0; e = e->next) {
            printf("%zu->%zu\n", u, e->v);
        }
    }

    puts("}");
}

struct edge {
    Vertex u;
    Vertex v;
};

// construct and return a DFS tree on g
// starting at root
Graph *
graphDFS(const Graph *g, Vertex root)
{
    // DFS tree holds parent pointers
    Vertex n = graphSize(g);
    Graph *dfs = graphCreate(n);

    // stack holds unexplored edges
    struct edge *stack = calloc(graphEdgeCount(g), sizeof(struct edge));
    size_t top = 0;

    // push root->root onto the stack
    stack[top].u = root;
    stack[top].v = root;
    top++;

    while(top > 0) {
        // stack not empty
        struct edge next = stack[--top];

        if(dfs->alist[next.v] == 0) {
            // haven't reached next.v yet
            // add parent pointer
            graphAddEdge(dfs, next.v, next.u);

            // add all outgoing edges
            struct edge out;
            out.u = next.v;

            for(struct elt *e = g->alist[next.v]; e != 0; e = e->next) {
                out.v = e->v;
                stack[top++] = out;
            }
        }
    }

    free(stack);

    return dfs;
}

// construct and return a BFS tree on g
// starting at root
Graph *
graphBFS(const Graph *g, Vertex root)
{
    // BFS tree holds parent pointers
    Vertex n = graphSize(g);
    Graph *bfs = graphCreate(n);

    // queue holds unexplored edges
    // extra space for fake root->root edge
    struct edge *queue = calloc(graphEdgeCount(g)+1, sizeof(struct edge));
    size_t head = 0;  // next position to pop
    size_t tail = 0;  // next position to push


    // push root->root onto the queue
    queue[tail].u = root;
    queue[tail].v = root;
    tail++;

    while(head < tail) {
        // queue not empty
        struct edge next = queue[head++];

        if(bfs->alist[next.v] == 0) {
            // haven't reached next.v yet
            // add parent pointer
            graphAddEdge(bfs, next.v, next.u);

            // add all outgoing edges
            struct edge out;
            out.u = next.v;

            for(struct elt *e = g->alist[next.v]; e != 0; e = e->next) {
                out.v = e->v;
                queue[tail++] = out;
            }
        }
    }

    free(queue);

    return bfs;
}


#ifdef TEST_MAIN

#define N (10)

int
main(int argc, char **argv)
{
    Graph *g = graphCreate(N);

    for(Vertex i = 0; i < N; i++) {
        graphAddEdge(g, i, (i+1) % N);
        graphAddEdge(g, i, (i+3) % N);
    }

    assert(graphSize(g) == N);
    assert(graphEdgeCount(g) == 2*N);

    graphPrint(g, stdout);
 
    Graph *dfs = graphDFS(g, 0);
    // graphPrint(dfs, stdout);
  
    Graph *bfs = graphBFS(g, 0);
    // graphPrint(bfs, stdout);

    graphDestroy(bfs);
    graphDestroy(dfs);
    graphDestroy(g);

    return 0;
}


#endif // TEST_MAIN
