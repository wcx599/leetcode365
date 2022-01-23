// Graph data structure for computing distance-2 colorings

typedef struct graph *Graph;

// Read a graph from a FILE *.
// Format is n on first line, followed by
// edges as pairs of vertices on subsequent lines.
// Returns 0 on error.
Graph graphRead(FILE *);

// Free all space used by a graph
void graphDestroy(Graph);

// Return the number of vertices in a graph
size_t graphSize(Graph);

// Compute a distance-2 coloring for a graph g.
// Return value is an array of size graphSize(g).
size_t *graphDistance2Coloring(Graph g);

#define COLORING_OK (0)            // coloring works
#define COLORING_OUT_OF_RANGE (1)  // color out of range
#define COLORING_CONFLICT (2)      // two neighbors with same color

// Check a distance-2 coloring for a graph g.
// Returns one of the status codes above.
int graphDistance2ColoringCheck(Graph g, size_t *coloring);
