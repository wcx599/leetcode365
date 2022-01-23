typedef struct node **Tree;

Tree treeCreate(void);
void treeDestroy(Tree);

// add key to tree
void treeInsert(Tree, int key);

// return 1 if key is in tree
int treeSearch(Tree, int key);

// return number of keys in tree
size_t treeSize(Tree);

// print tree to stdout
void treePrint(Tree);
