#include <iostream>

using namespace std;

int fail()
{ 
    throw "you lose";

    return 5;
}

int
main(int argc, const char **argv)
{
    try {
        cout << fail() << '\n';
    } 
    catch(const char *s) {
        cerr << "Caught error: " << s << '\n';
    }

    return 0;
}
