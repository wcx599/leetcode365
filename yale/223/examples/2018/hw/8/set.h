// set of words
typedef struct set Set;

// new empty set
Set *setCreate(void);

// destroy a set
void setDestroy(Set *);

// add a word to a set
void setInsert(Set *, const char *key);

// return 1 if set contains key, 0 otherwise
int setContains(const Set *, const char *key);
