#include <iostream>

using namespace std;

/* an intRange represents the numbers x such that
 * min <= x < max */
class intRange {
    int min;
    int max;
public:
    intRange(int, int);   /* constructor */
    int contains(int);
};

intRange::intRange(int lo, int hi)
{
    min = lo;
    max = hi;
}

int 
intRange::contains(int x)
{
    return (min <= x) && (x < max);
}

int
main(int argc, const char **argv)
{
    intRange r(0, 10);

    cout << "r.contains(-3) == " << r.contains(-3) << '\n';
    cout << "r.contains(5) == " << r.contains(5) << '\n';
    cout << "r.contains(12) == " << r.contains(12) << '\n';

    return 0;
}
