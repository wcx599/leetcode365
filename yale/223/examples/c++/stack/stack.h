template <class T>
class Stack {
    static const int initialSize = 32;   /* static means this is shared across entire class */
    int top;
    int size;
    T* contents;
public:
    Stack();          /* create a new empty stack */

    /* the unholy trinity of complex C++ objects */
    ~Stack();         /* destructor */
    Stack(const Stack &);     /* copy constructor */
    Stack& operator=(const Stack &); /* overloaded assignment */

    void push(T);     /* push an element onto the stack */
    int isEmpty();    /* return 1 if empty */
    T pop();          /* pop top element from stack */
};

template <class T>
Stack<T>::Stack() 
{ 
    size = initialSize;
    top = 0;
    contents = new T[size];
}

template <class T> 
Stack<T>::~Stack()
{ 
    delete [] contents;
}

template <class T>
Stack<T>::Stack(const Stack<T> &other)
{
    size = other.size;
    top = other.top;
    contents = new T[size];

    for(int i = 0; i < top; i++) {
        contents[i] = other.contents[i];
    }
}

template <class T>
Stack<T> &
Stack<T>::operator=(const Stack<T> &other)
{
    if(&other != this) {
        /* this is a real assignment */

        delete [] contents;

        size = other.size;
        top = other.top;
        contents = new T[size];

        for(int i = 0; i < top; i++) {
            contents[i] = other.contents[i];
        }
    }
    
    return *this;
}

template <class T>
void 
Stack<T>::push(T elt)
{
    if(top >= size) {
        int newSize = 2*size;
        T *newContents = new T[newSize];

        for(int i = 0; i < top; i++) {
            newContents[i] = contents[i];
        }

        delete [] contents;

        contents = newContents;
        size = newSize;
    }
        
    contents[top++] = elt;
}

template <class T>
T
Stack<T>::pop()
{
    if(top > 0) {
        return contents[--top];
    } else {
        throw "stack empty";
    }
}
