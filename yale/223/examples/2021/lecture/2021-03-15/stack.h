// abstract stack data structure for holding ints
//
// top -> 1 2 3
//
// push(5)
//
// top -> 5 1 2 3
//
// pop() -> 5
//
// 1 2 3

typedef struct stack *Stack;

// make a new empty stack
Stack stackCreate(void);

// free all space used by s
void stackDestroy(Stack s);

// push a new value on top of the stack
void stackPush(Stack s, int v);

// returns 1 if stack is empty, 0 otherwise
int stackEmpty(Stack s);

// pop top value from a nonempty stack
int stackPop(Stack s);

// print contents of stack, starting from top
void stackPrint(Stack s);
