#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "graph.h"
#include "search.h"

// internal routine to set up search data
static SearchData 
searchDataCreate(Graph g)
{
    SearchData s = malloc(sizeof(*s));
    assert(s);

    s->parent = calloc(g->n, sizeof(Node));
    assert(s->parent);

    for(Node i = 0; i < g->n; i++) {
        s->parent[i] = NODE_NULL;
    }

    return s;
}

// search subtree starting at root
static void
searchDFSInternal(Graph g, Node root, SearchData s)
{
    // throw in all unvisited kids
    for(Node i = 0; i < g->u[root]->d; i++) {
        Node child = g->u[root]->v[i];

        if(s->parent[child] == NODE_NULL) {
            // haven't visited it, throw it in
            s->parent[child] = root;
            searchDFSInternal(g, child, s);
        }
    }
}

// Do a DFS search on graph starting at given node.
// Note: This implementation WILL BLOW OUT THE STACK
// on large graphs.
SearchData
searchDFS(Graph g, Node root)
{
    SearchData s = searchDataCreate(g);

    // start by adding root
    s->parent[root] = root;  // convention to get non-null parent

    // search all kids of root recursively
    searchDFSInternal(g, root, s);

    return s;
}

// Do a BFS search on graph
// starting at given node
SearchData 
searchBFS(Graph g, Node root)
{
    SearchData s = searchDataCreate(g);

    // Build my own queue of nodes
    Node *q = calloc(g->n, sizeof(Node));
    Node head = 0;   // enqueue elements here
    Node tail = 0;   // dequeue elements here

    // put root in queue
    q[head++] = root;
    s->parent[root] = root;

    while(tail < head) {
        // q is not empty
        Node current = q[tail++];

        // check all outgoing edges from current
        for(Node j = 0; j < g->u[current]->d; j++) {
            Node child = g->u[current]->v[j];

            if(s->parent[child] == NODE_NULL) {
                // adopt child as our own
                s->parent[child] = current;

                // add it to the queue
                q[head++] = child;
            }
        }
    }

    return s;
}

// always clean up
void 
searchDataDestroy(SearchData s)
{
    free(s->parent);
    free(s);
}

// Helpers for searchTree
static Node
searchTreeDegree(Node n, Node i, void *data)
{
    SearchData s = data;
    Node parent = s->parent[i];

    if(parent != NODE_NULL && parent != i) {
        return 1;
    } else {
        return 0;
    }
}

static Node
searchTreeNeighbor(Node n, Node i, Node j, void *data)
{
    SearchData s = data;
    Node parent = s->parent[i];

    assert(j == 0 && parent != NODE_NULL && parent != i);

    return parent;
}

// Construct search tree from Graph and searchData.
// This is a rooted tree with edges from children to parents.
Graph 
searchTree(Graph g, SearchData s)
{
    return graphGenerate(g->n, searchTreeDegree, searchTreeNeighbor, s);
}
