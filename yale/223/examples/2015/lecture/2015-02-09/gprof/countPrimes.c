/* count the prime numbers less than n, where n is argv[1] */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <math.h>

/* return 1 if n is prime */
int 
isPrime(int n)
{
    int f;
    int s;

    /* special case for 2 because it is prime */
    if(n % 2 == 0 && n > 2) {
        return 0;
    }

    s = sqrt(n) + 1;
    for(f = 3; f <= s; f += 2) {
        if(n % f == 0) {
            return 0;
        }
    }

    return 1;
}

int
main(int argc, char **argv)
{
    int n;
    int i;
    int count = 0;

    if(argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);

    for(i = 0; i < n; i++) {
        if(isPrime(i)) {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}
