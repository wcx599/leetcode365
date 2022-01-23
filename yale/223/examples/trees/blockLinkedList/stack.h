/* basic stack interface */

typedef struct stack *Stack;

/* create an empty stack */
Stack stackCreate(void);

/* free a stack */
void stackDestroy(Stack);

/* stack operations */
int stackIsEmpty(Stack);
void stackPush(Stack, int);
int stackPop(Stack);
