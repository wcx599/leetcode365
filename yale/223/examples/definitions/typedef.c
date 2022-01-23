#include <stdio.h>

typedef const char *t1;
typedef const char *t2;

int
main(int argc, char **argv)
{
    t1 a;
    t2 b;

    /* Even though a and b are declared using different typedef
     * names, as far as the compiler is concerned they are both
     * of type const char *. */
    a = "foo";
    b = a;

    puts(b);

    return 0;
}
