#include <iostream>
#include <cassert>
#include <cstring>

#include "boundedArray.h"

using namespace std;

int
main(int argc, const char **argv)
{
    BoundedArray<int> a(10);
    BoundedArray<int> a2(5);
    BoundedArray<const char *> s(5);

    s[0] = "hi";
    
    for(int i = 0; i < 10; i++) {
        a[i] = i;
        assert(a[i] == i);
    }

    a2 = a;

    for(int i = 0; i < 10; i++) {
        assert(a2[i] == i);
        a[i] = i+1;
        assert(a[i] == i+1);
        assert(a2[i] == i);
    }

    try {
        a[11];
        assert(0);  // bounds test failed
    } catch(const char *err) {
        assert(!strcmp(err, "out of bounds"));
    }

    return 0;
}





