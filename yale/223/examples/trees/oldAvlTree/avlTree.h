/* implementation of an AVL tree with explicit heights */

typedef struct avlNode *AvlTree;

/* empty avl tree is just a null pointer */

#define AVL_EMPTY (0)

/* free a tree */
void avlDestroy(AvlTree t);

/* return the height of a tree */
int avlGetHeight(AvlTree t);

/* return nonzero if key is present in tree */
int avlSearch(AvlTree t, int key);

/* insert a new element into a tree */
/* note *t is actual tree */
void avlInsert(AvlTree *t, int key);

/* run sanity checks on tree (for debugging) */
/* assert will fail if heights are wrong */
void avlSanityCheck(AvlTree t);

/* print all keys of the tree in order */
void avlPrintKeys(AvlTree t);

/* delete and return minimum value in a tree */
int avlDeleteMin(AvlTree *t);
