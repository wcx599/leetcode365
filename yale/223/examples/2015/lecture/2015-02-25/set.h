/*
 * Abstract data type of sets of void *s.
 */

struct elementOps { 
    /* whatever extra data we need to make these functions work */
    void *env;     

    size_t (*hash)(void *env, const void *elt);   /* hash an elt */

    /* return >0 if e1 > e2, 0 if equal, <0 if e1 < e2 */
    int (*compare)(void *env, const void *e1, const void *e2);

    /* copy an element */
    void * (*copy)(void *env, const void *elt);

    /* destroy an element, feeing all space */
    void (*destroy)(void *env, void *elt);
};

/* make a new set */
struct set *setCreate(const struct elementOps *);   /* constructor */

/* free up space used by set */
void setDestroy(struct set *);  /* destructor */

/* add x to set */
void setInsert(struct set *, const void *x);

/* remove x from set */
void setDelete(struct set *, const void *x);

/* test membership, return true if x is in set */
int setMember(const struct set *, const void *x);

/* run function f on every element of the set */
void setForeach(const struct set *, void (*f)(void *env, const void *elt), void *env);
