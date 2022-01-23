#include <iostream>
#include <stack>

using namespace std;

int
main(int argc, const char **argv)
{
    stack<int> s;
    stack<int> s2;

    s.push(1);
    s.push(2);
    s.push(3);

    s2 = s;

    cout << s.top() << '\n'; s.pop();
    cout << s.top() << '\n'; s.pop();
    cout << s.top() << '\n'; s.pop();

    cout << s2.top() << '\n'; s2.pop();
    cout << s2.top() << '\n'; s2.pop();
    cout << s2.top() << '\n'; s2.pop();

    for(int i = 0; i < 1000; i++) {
        s.push(i);
    }

    cout << s.top() << '\n';

    return 0;
}
