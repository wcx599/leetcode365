#include <iostream>

#include "stack.h"

using namespace std;

int
main(int argc, const char **argv)
{
    Stack<int> s;
    Stack<int> s2;

    try {
        s.push(1);
        s.push(2);
        s.push(3);

        s2 = s;

        cout << s.pop() << '\n';
        cout << s.pop() << '\n';
        cout << s.pop() << '\n';

        cout << s2.pop() << '\n';
        cout << s2.pop() << '\n';
        cout << s2.pop() << '\n';

        try {
            s2.pop();
        } catch(const char *err) {
            cout << "Caught expected exception " << err << '\n';
        }

        for(int i = 0; i < 1000; i++) {
            s.push(i);
        }

        cout << s.pop() << '\n';
    } catch(const char *err) {
        cerr << "Caught error " << err << '\n';
    }

    return 0;
}
