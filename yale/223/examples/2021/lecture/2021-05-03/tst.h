// String set data structure implemented
// as a ternary search tree

typedef struct tst *Tst;

#define TST_EMPTY (0)

// Add a new element to a TST.
// Call as tstInsert(&t, s) to allow updating.
void tstInsert(Tst *, const char *);

int tstContains(const Tst, const char *);

// Print all strings in Tst that start with prefix
void tstPrintCompletions(Tst, const char *prefix);

// Print a pictorial representation of Tst
void tstShow(Tst);

// Destroy a TST
void tstDestroy(Tst);
