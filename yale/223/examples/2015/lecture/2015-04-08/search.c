#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

typedef int Vertex;

#define VERTEX_NULL (-1)

struct node {
    Vertex *neighbors;   /* array of outgoing edges, terminated by VERTEX_NULL */
    Vertex parent;       /* for search */
    size_t distance;     /* for search */
};

struct graph {
    size_t n;            /* number of vertices */
    struct node *v;      /* list of vertices */
};

void
graphDestroy(struct graph *g)
{
    Vertex v;

    for(v = 0; v < g->n; v++) {
        free(g->v[v].neighbors);
    }

    free(g);
}

/* this graph has edges from x to x+1, x to 3*x, and x to x/2 (when x is even) */
struct graph *
makeSampleGraph(size_t n)
{
    struct graph *g;
    Vertex v;
    const int allocNeighbors = 4;
    int i;

    g = malloc(sizeof(*g));
    assert(g);

    g->n = n;
    g->v = malloc(sizeof(struct node) * n);
    assert(g->v);

    for(v = 0; v < n; v++) {
        g->v[v].parent = VERTEX_NULL;
        g->v[v].distance = SIZE_MAX;

        /* fill in neighbors */
        g->v[v].neighbors = malloc(sizeof(Vertex) * allocNeighbors);
        i = 0;
        if(v % 2 == 0) { g->v[v].neighbors[i++] = v/2; }
        if(v+1 < n) { g->v[v].neighbors[i++] = v+1; }
        if(3*v < n) { g->v[v].neighbors[i++] = 3*v; }
        g->v[v].neighbors[i++] = VERTEX_NULL;
    }

    return g;
}

/* output graph in dot format */
void
printGraph(const struct graph *g)
{
    Vertex u;
    size_t i;

    puts("digraph G {");

    for(u = 0; u < g->n; u++) {
        for(i = 0; g->v[u].neighbors[i] != VERTEX_NULL; i++) {
            printf("%d -> %d;\n", u, g->v[u].neighbors[i]);
        }
    }

    puts("}");
}

/* reconstruct path back to root from u */
void
printPath(const struct graph *g, Vertex u)
{
    do {
        printf(" %d", u);
        u = g->v[u].parent;
    } while(g->v[u].parent != u);
}

#if 0
void
printTree(const struct graph *g)
{
    Vertex u;

    for(u = 0; u < g->n; u++) {
        if(g->v[u].parent == VERTEX_NULL) {
            printf("%d (not connected)\n", u);
        } else {
            printf("%d (distance %zu):", u, g->v[u].distance);
            printPath(g, u);
            putchar('\n');
        }
    }
}
#endif

/* print the tree in dot format */
void
printTree(const struct graph *g)
{
    Vertex u;

    puts("digraph G {");

    for(u = 0; u < g->n; u++) {
        if(g->v[u].parent != VERTEX_NULL) {
            printf("%d -> %d;\n", u, g->v[u].parent);
        }
    }

    puts("}");
}

/* compute BFS tree starting at root */
void
bfs(struct graph *g, Vertex root)
{
    Vertex *q;
    int head;   /* deq from here */
    int tail;   /* enq from here */
    Vertex current;
    Vertex nbr;
    int i;

    q = malloc(sizeof(Vertex) * g->n);
    assert(q);

    head = tail = 0;

    /* push root onto q */
    g->v[root].parent = root;
    q[tail++] = root;

    while(head < tail) {
        current = q[head++];

        for(i = 0; (nbr = g->v[current].neighbors[i]) != VERTEX_NULL; i++) {
            if(g->v[nbr].parent == VERTEX_NULL) {
                /* haven't seen this guy */
                /* push it */
                g->v[nbr].parent = current;
                q[tail++] = nbr;
            }
        }
    }

    free(q);
}



int
main(int argc, char **argv)
{
    int n;
    struct graph *g;

    if(argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);

    g = makeSampleGraph(n);

    bfs(g, 0);

    printTree(g);

    graphDestroy(g);

    return 0;
}
