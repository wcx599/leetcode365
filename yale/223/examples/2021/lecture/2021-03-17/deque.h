// implement a deque

typedef struct deque *Deque;

// constructor
Deque dequeCreate(void);

// destructor
void dequeDestroy(Deque);

#define LEFT (0)
#define RIGHT (1)

// mutators/accessors
void dequeEnq(Deque, int direction, int);
int dequeDeq(Deque, int direction);

// accessor
int dequeIsEmpty(Deque);
