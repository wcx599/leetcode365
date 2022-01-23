// alternative interface to tree
// here we do not hide the top-level
// pointer, but we have to modify the
// interface to treeInsert to either
// using a pointer to give access to it,
// or to return the new pointer if we don't
// (treeInsertFunctional)
//
// Both these approaches impose more cognitive
// load on the user, which is why I like the
// interface in tree.h better.

typedef struct node *Tree;

Tree treeCreate(void);
void treeDestroy(Tree);

// add key to tree
// call like treeInsert(&tree, key)
void treeInsert(Tree *, int key);

// returns new tree
// this is an alternative that avoids passing
// a pointer
Tree treeInsertFunctional(Tree, int key);

// return 1 if key is in tree
int treeSearch(Tree, int key);

// print tree to stdout
void treePrint(Tree);
