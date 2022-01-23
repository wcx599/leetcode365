#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    int x;
    double d;

    // %d means eat initial whitespace then read a decimal value
    // &x is pointer to place to store this value
    scanf("%d%lf", &x, &d);
    printf("%d %lf\n", x, d);

    if((scanf(" [%d]", &x)) != 1) {
        puts("scanf failed");
    } else {
        printf("%d\n", x);
    }

#if 0
    // keep reading ints until we run out or hit an error
    while(scanf("%d", &x) == 1) {
        printf("%d\n", x);
    }
#endif

    return 0;
}
