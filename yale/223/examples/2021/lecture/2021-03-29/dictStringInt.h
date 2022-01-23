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

// iterate over all pairs in table, allowing function f
// to operate on them and data
void dictStringIntForeach(DictStringInt,
        void (*f)(const char *, int *, void *),
        void *data);
