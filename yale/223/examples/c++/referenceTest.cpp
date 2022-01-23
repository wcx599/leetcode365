#include <iostream>
#include <cstdio>

using namespace std;

void refTest(int &x)
{
    printf("&x inside refTest is %p\n", &x);
}

int
main(int argc, const char **argv)
{
    int x;

    printf("&x inside main is %p\n", &x);

    refTest(x);

    return 0;
}
