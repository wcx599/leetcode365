// dictionary data type mapping strings to ints
// default value is 0
typedef struct dictStringInt *DictStringInt;

DictStringInt dictStringIntCreate(void);
void dictStringIntDestroy(DictStringInt);

// returns pointer to matching int location
// this may not remain valid after another
// call to dictStringIntLookup.
int *dictStringIntLookup(DictStringInt, const char *);

// print all pairs in table
void dictStringIntPrint(DictStringInt, FILE *);
