#include <stdio.h>
#include <stdlib.h>

/* print prime factors of n */

int
main(int argc, char **argv)
{
    unsigned long long n;
    unsigned long long f;

    if(argc != 2) {
        fprintf(stderr, "Usage: %s number-to-factor\n", argv[0]);
        return 1;
    }

    n = atoll(argv[1]);

    while(n % 2 == 0) {
        printf("%d\n", 2);
        n /= 2;
    }

    for(f = 3; f <= n; f += 2) {
        while(n % f == 0) {
            printf("%lld\n", f);
            n /= f;
        }
    }

    return 0;
}
