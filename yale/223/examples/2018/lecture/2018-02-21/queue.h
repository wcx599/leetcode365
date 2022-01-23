typedef struct q Q;

typedef int elt;

// new empty queue
Q *qCreate(void);

void qDestroy(Q *);

// add an element to the end
void enq(Q *, elt);

// deletes and return first elt
elt deq(Q *);

// is the queue empty?
int qEmpty(const Q *);
