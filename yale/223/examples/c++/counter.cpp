#include <iostream>

using namespace std;

/* counters can be incremented or read */
class Counter {
    int value;            /* private value */
public:
    Counter();            /* constructor with default value */
    Counter(int);         /* constructor with specified value */
    ~Counter();           /* useless destructor */
    int read();           /* get the value of the counter */
    void increment();     /* add one to the counter */
};

Counter::Counter() { value = 0; }
Counter::Counter(int initialValue) { value = initialValue; }
Counter::~Counter() { cerr << "counter de-allocated with value " << value << '\n'; }
int Counter::read() { return value; }
void Counter::increment() { value++; }

int
main(int argc, const char **argv)
{
    Counter c;
    Counter c10(10);

    cout << "c starts at " << c.read() << '\n';
    c.increment();
    cout << "c after one increment is " << c.read() << '\n';

    cout << "c10 starts at " << c10.read() << '\n';
    c.increment();
    c.increment();
    cout <<"c10 after two increments is " << c10.read() << '\n';

    return 0;
}
