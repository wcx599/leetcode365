/* returns 1 if n is prime, 0 otherwise */
int
isPrime(int n)
{
    int i;

    if (n < 2) return 0;   /* special case for 0, 1, negative n */
 
    for(i = 2; i < n; i++) {
        if (n % i == 0) {
            /* found a factor */
            return 0;
        }
    }

    /* no factors */
    return 1;
}
