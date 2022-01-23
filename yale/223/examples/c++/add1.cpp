#include <iostream>
#include <algorithm> // for max

using namespace std;

/* act like ints, except + does max and * does addition */
class MaxPlus {
    int value;
public:
    MaxPlus(int);
    MaxPlus operator+(MaxPlus);
    MaxPlus operator*(MaxPlus);
    operator int();
};

MaxPlus::MaxPlus(int x) { value = x; }

MaxPlus 
MaxPlus::operator*(MaxPlus other)
{
    return MaxPlus(value + other.value);
}

MaxPlus 
MaxPlus::operator+(MaxPlus other)
{
    /* std::max does what you expect */
    return MaxPlus(max(value, other.value));
}

MaxPlus::operator int() { return value; }

template <class T>
T add1(T x)
{
    return x + ((T) 1);
}

int
main(int argc, const char **argv)
{
    cout << "add1(3) == " << add1(3) << '\n';
    cout << "add1(3.1) == " << add1(3.1) << '\n';
    cout << "add1('c') == " << add1('c') << '\n';
    cout << "add1(MaxPlus(0)) == " << add1(MaxPlus(0)) << '\n';
    cout << "add1(MaxPlus(2)) == " << add1(MaxPlus(2)) << '\n';
    cout << "add1<int>(3.1) == " << add1<int>(3.1) << '\n';

    return 0;
}
