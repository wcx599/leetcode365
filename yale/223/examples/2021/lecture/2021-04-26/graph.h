// Minimalist graph implementation

// Non-opaque data structure.
// We want to let users do whatever they want with this.
struct graph {
    size_t n;             // number of vertices
    struct neighbors *u[]; // adjacency lists
};

typedef struct graph *Graph;

struct neighbors {
    size_t d;   // degree of this node
    size_t v[]; // list of outgoing neighbors
};

// Print graph in DOT format
void graphPrint(Graph, FILE *);

// Generic graph builder.
// Function degree returns degree of node i.
// Function neighbor returns j-th neighbor of node i.
// Parameter data is passed to both functions.
Graph graphGenerate(
        size_t n,
        size_t (*degree)(size_t n, size_t i, void *data),
        size_t (*neighbor)(size_t n, size_t i, size_t j, void *data),
        void *data);

// some standard graphs
Graph graphComplete(size_t n);
Graph graphDirectedCycle(size_t n);
Graph graphBinaryTree(size_t n);
Graph graphHypercube(size_t n); // n must be power of 2

// free a graph
void graphDestroy(Graph);

// copy a graph
Graph graphCopy(Graph);
