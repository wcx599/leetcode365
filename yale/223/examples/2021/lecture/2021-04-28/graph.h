// Minimalist graph implementation

typedef size_t Node;

#define NODE_NULL (SIZE_MAX)

// Non-opaque data structure.
// We want to let users do whatever they want with this.
struct graph {
    Node n;             // number of vertices
    struct neighbors *u[]; // adjacency lists
};

typedef struct graph *Graph;

struct neighbors {
    Node d;   // degree of this node
    Node v[]; // list of outgoing neighbors
};

// Print graph in DOT format
void graphPrint(Graph, FILE *);

// Generic graph builder.
// Function degree returns degree of node i.
// Function neighbor returns j-th neighbor of node i.
// Parameter data is passed to both functions.
Graph graphGenerate(
        Node n,
        Node (*degree)(Node n, Node i, void *data),
        Node (*neighbor)(Node n, Node i, Node j, void *data),
        void *data);

// some standard graphs
Graph graphComplete(Node n);
Graph graphDirectedCycle(Node n);
Graph graphBinaryTree(Node n);
Graph graphHypercube(Node n); // n must be power of 2
Graph graphCompleteBipartite(Node left, Node right);

// free a graph
void graphDestroy(Graph);

// copy a graph
Graph graphCopy(Graph);
