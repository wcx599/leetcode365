/* 
 * Basic priority queue implementation.
 */

typedef uint64_t HeapElement;    /* so we can change it if we need to */

struct heap *heapCreate(void);   /* make a new heap */

void heapDestroy(struct heap *); /* deallocate the heap */

void heapInsert(struct heap *, HeapElement);  /* add a new element */

HeapElement heapDeleteMin(struct heap *);     /* delete and return first element */

size_t heapSize(const struct heap *);   /* how many elements are in the heap */
