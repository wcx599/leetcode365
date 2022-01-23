typedef struct node **Tree;

Tree treeCreate(void);
void treeDestroy(Tree);

// add key to tree
void treeInsert(Tree, int key);

// remove key to tree
// no effect if tree is not in key
void treeDelete(Tree, int key);

// return 1 if key is in tree
int treeSearch(Tree, int key);

// return number of keys in tree
size_t treeSize(Tree);

// find element with rank elements below it
// if k is too big, aborts
int treeSearchByRank(Tree, size_t rank);

// print tree to stdout
void treePrint(Tree);
