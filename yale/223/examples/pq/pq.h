/* generic priority queue */

typedef struct pq *PQ;

/* create a new empty priority queue */
/* elementLength is the size of an element in bytes */
/* compare is a comparision function that returns
 * <0 if its first argument is less than its second
 *  0 if they are equal
 * >0 if the first argument is greater than the second. */ 
PQ pqCreate(int elementLength, int (*compare)(const void *, const void *));

/* free a priority queue */
void pqDestroy(PQ);

/* add an element to the priority queue */
/* the contents of the element are COPIED from elt */
void pqInsert(PQ, const void *elt);

/* returns nonzero if PQ is empty */
int pqIsEmpty(PQ);

/* delete the minimum element of the priority queue */
/* and COPY its contents to retval */
/* it is an error to call this on an empty queue */
void pqDeleteMin(PQ, void *retval);

/* utility function: blows up if heap invariant is violated */
void pqSanityCheck(PQ);
