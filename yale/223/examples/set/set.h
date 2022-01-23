/* generic set */

typedef struct set *Set;

/* create a new empty set */
/* elementLength is the size of an element in bytes */
/* two elements are assumed equal if they have the same contents */
/* (this is not entirely safe for structs with padding) */
Set setCreate(size_t elementLength);

/* free a set */
void setDestroy(Set);

/* add an element to a set */
void setInsert(Set, const void *elt);

/* return nonzero if an element is in the set */
int setContains(Set, const void *elt);
