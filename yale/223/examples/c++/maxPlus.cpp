#include <iostream>
#include <algorithm> // for max

using namespace std;

/* act like ints, except + does max and * does addition */
class MaxPlus {
    int value;
public:
    MaxPlus(int);
    MaxPlus operator+(const MaxPlus &);
    MaxPlus operator*(const MaxPlus &);
    operator int();
};

MaxPlus::MaxPlus(int x) { value = x; }

MaxPlus 
MaxPlus::operator*(const MaxPlus &other)
{
    return MaxPlus(value + other.value);
}

MaxPlus 
MaxPlus::operator+(const MaxPlus &other)
{
    /* std::max does what you expect */
    return MaxPlus(max(value, other.value));
}

MaxPlus::operator int() { return value; }

int
main(int argc, const char **argv)
{
    cout << "2+3 == " << (MaxPlus(2) + MaxPlus(3)) << '\n';
    cout << "2*3 == " << (MaxPlus(2) * MaxPlus(3)) << '\n';

    return 0;
}
