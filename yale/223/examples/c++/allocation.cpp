#include <iostream>
#include <cassert>

using namespace std;

class Noisy {
    int id;
public:
    Noisy(int);  // create a noisy object with this id
    ~Noisy();
};

Noisy::Noisy(int initId) { 
    id = initId;
    cout << "Noisy object created with id " << id << '\n';
}

Noisy::~Noisy() { 
    cout << "Noisy object destroyed with id " << id << '\n';
}

int
main(int argc, const char **argv)
{
    int *p;
    int *a;
    const int n = 100;
    Noisy n1(1);
    Noisy *n2;

    p = new int;
    a = new int[n];
    n2 = new Noisy(2);

    *p = 5;
    assert(*p == 5);

    for(int i = 0; i < n; i++) {
        a[i] = i;
    }

    for(int i = 0; i < n; i++) {
        assert(a[i] == i);
    }

    delete [] a;
    delete p;
    delete n2;

    return 0;
}
