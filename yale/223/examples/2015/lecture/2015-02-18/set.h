/*
 * Abstract data type of sets of ints.
 */

/* make a new set */
struct set *setCreate(void);   /* constructor */

/* free up space used by set */
void setDestroy(struct set *);  /* destructor */

/* add x to set */
void setInsert(struct set *, int x);

/* remove x from set */
void setDelete(struct set *, int x);

/* test membership, return true if x is in set */
int setMember(const struct set *, int x);


