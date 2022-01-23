#ifndef _GRAPH_H
#define _GRAPH_H

// basic abstract graph type

#include <stdio.h>
#include <stdint.h> // for SIZE_MAX

// this can come in handy
#define NULL_VERTEX (SIZE_MAX)

typedef size_t Vertex;

typedef struct graph Graph;

// create a graph with n vertices
Graph *graphCreate(Vertex n);

// destroy a graph
void graphDestroy(Graph *);

// add an edge uv
void graphAddEdge(Graph *, Vertex u, Vertex v);

// return number of vertices in a graph
Vertex graphSize(const Graph *);

// return number of edges in a graph
size_t graphEdgeCount(const Graph *);

// print a graph to FILE in GraphViz input format
void graphPrint(const Graph *, FILE *);

// construct a DFS tree for g starting at root
// this is a new graph with the same vertices as g,
// but whose edges are parent pointers
Graph *graphDFS(const Graph *g, Vertex root);

// construct a DFS tree for g starting at root
// this is a new graph with the same vertices as g,
// but whose edges are parent pointers
Graph *graphBFS(const Graph *g, Vertex root);

// return list of outgoing neighbors
// terminated by NULL_VERTEX
// caller must free list
Vertex *graphNeighbors(const Graph *g, Vertex u);

#endif // _GRAPH_H
