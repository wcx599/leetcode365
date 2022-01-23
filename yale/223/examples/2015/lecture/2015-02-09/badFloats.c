#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <math.h>

int
main(int argc, char **argv)
{
    float x;
    int i;

    x = 0.1234567890123456789;
    printf("%0.15g\n", x);

    x = 1.0e-17 * 1.0e-17 * 1.0e-17;
    printf("%g\n", x);

    x = 2e150;
    printf("x*x == %g, x*x*x == %g\n", x*x, x*x*x);

    printf("0/0 == %g\n", 0.0 / 0.0);

    i = (1 << 30) + 37;
    x = i;

    printf("i == %d, x = %0.20g\n", i, x);

    printf("%d %g %g\n", 5/3, (double) 5 / (double) 3, 5.0 / 3);

    printf("sqrt(2) == %g\n", sqrt(2));

    return 0;
}
