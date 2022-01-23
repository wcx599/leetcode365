#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "graph.h"

void
graphPrint(Graph g, FILE *f)
{
    fprintf(f, "digraph {\n");
    for(Node i = 0; i < g->n; i++) {
        Node d = g->u[i]->d;
        if(d > 0) {
            fprintf(f, "%zu->{", i);
            for(Node j = 0; j < d-1; j++) {
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
    Node n,
    Node (*degree)(Node n, Node i, void *data),
    Node (*neighbor)(Node n, Node i, Node j, void *data),
    void *data)
{
    Graph g = malloc(sizeof(struct graph) + sizeof(struct neighbors *) * n);
    assert(g);

    g->n = n;

    for(Node i = 0; i < n; i++) {

        Node d = degree(n, i, data);
        g->u[i] = malloc(sizeof(struct neighbors) + sizeof(Node) * d);
        assert(g->u[i]);
        g->u[i]->d = d;

        for(Node j = 0; j < d; j++) {
            g->u[i]->v[j] = neighbor(n, i, j, data);
        }
    }

    return g;
}

static Node
degreeFixed(Node n, Node i, void *data)
{
    Node *d = data;
    return *d;
}

static Node
neighborComplete(Node n, Node i, Node j, void *data)
{
    // we need to be a little careful to skip i
    if(j >= i) {
        return j+1;
    } else {
        return j;
    }
}

Graph
graphComplete(Node n)
{
    Node d = n-1;

    return graphGenerate(n, degreeFixed, neighborComplete, &d);
}

static Node
neighborDirectedCycle(Node n, Node i, Node j, void *data)
{
    assert(j == 0);
    return (i+1) % n;
}

Graph
graphDirectedCycle(Node n)
{
    Node d = 1;

    return graphGenerate(n, degreeFixed, neighborDirectedCycle, &d);
}

static Node
binaryTreeNeighbor(Node n, Node i, Node j, void *data)
{
    return 2*i + j + 1;
}

static Node
binaryTreeDegree(Node n, Node i, void *data)
{
    Node d = 0;
    for(int j = 0; j <= 1; j++) {
        if(binaryTreeNeighbor(n, i, j, data) < n) {
            d++;
        }
    }

    return d;
}

// rooted binary tree based on packed heap
Graph
graphBinaryTree(Node n)
{
    return graphGenerate(n, 
            binaryTreeDegree,
            binaryTreeNeighbor,
            0);
}

static Node
hypercubeNeighbor(Node n, Node i, Node j, void *data)
{
    return i^(1 << j);
}

Graph
graphHypercube(Node n)
{
    Node logn;

    for(logn = 0; (1<<logn) < n; logn++);

    // bad things will happen if n is not a power of 2
    assert(1 << logn == n);

    return graphGenerate(n, degreeFixed, hypercubeNeighbor, &logn);
}

void
graphDestroy(Graph g)
{
    for(Node i = 0; i < g->n; i++) {
        free(g->u[i]);
    }
    free(g);
}

static Node
graphCopyDegree(Node n, Node i, void *data)
{
    Graph g2 = data;
    return g2->u[i]->d;
}

static Node
graphCopyNeighbor(Node n, Node i, Node j, void *data)
{
    Graph g2 = data;
    return g2->u[i]->v[j];
}

Graph
graphCopy(Graph g)
{
    return graphGenerate(g->n, graphCopyDegree, graphCopyNeighbor, g);
}

struct completeBipartite {
    Node left;  // how many nodes on left side
    Node right; // how many nodes on right side
};

static Node
completeBipartiteDegree(Node n, Node i, void *data)
{
    struct completeBipartite *d = data;

    if(i < d->left) {
        return d->right;
    } else {
        return 0;
    }
}

static Node
completeBipartiteNeighbor(Node n, Node i, Node j, void *data)
{
    struct completeBipartite *d = data;

    assert(i < d->left);

    return d->right + j;
}

Graph
graphCompleteBipartite(Node left, Node right)
{
    struct completeBipartite d = { left, right };

    return graphGenerate(left + right,
            completeBipartiteDegree,
            completeBipartiteNeighbor,
            &d);
}
