// graph search routines
// load graph.h before this header file

// Used to return info from DFS and BFS search.
// Mostly this is a struct to allow for potential
// expansion if we decide to return more data.
struct searchData {
    Node *parent;      // Array of parent indices
};

typedef struct searchData *SearchData;

// Do a DFS search on graph
// starting at given node
SearchData searchDFS(Graph, Node);

// Do a BFS search on graph
// starting at given node
SearchData searchBFS(Graph, Node);

// always clean up
void searchDataDestroy(SearchData);

// Construct search tree from Graph
// and searchData
Graph searchTree(Graph, SearchData);
