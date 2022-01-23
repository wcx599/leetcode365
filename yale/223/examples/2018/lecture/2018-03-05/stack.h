// basic stack implementation
// stack is a pointer to its first element
// caller will keep a pointer to this
typedef struct elt *Stack;

// truncated version of an object
// real object will have more fields after methods
struct object {
    const struct methods *methods;
};

struct methods {
    struct object *(*clone)(const struct object *self);
    void (*print)(const struct object *self);
    void (*destroy)(struct object *self);
};

// create and destroy stacks
Stack *stackCreate(void);
void stackDestroy(Stack *);

// usual functions
void stackPush(Stack *s, struct object *);

// don't call this on an empty stack
struct object *stackPop(Stack *s);

// returns true if not empty
int stackNotEmpty(const Stack *s);

// print the elements of a stack to stdout
// using function print
void stackPrint(const Stack *s);
