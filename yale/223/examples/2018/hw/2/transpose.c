/*
 * Transposition block cipher encoder/decoder.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* 
 * transpose in to out by the rule
 * out[i] = in[(a*i+b)%n];
 */
void
transpose(const char *in, char *out, int n, int a, int b)
{
    /* we need to do some sneakery to deal with negative remainders */
    long long j;

    for(long long i = 0; i < n; i++) {

        j = (a * i + b) % n;
        if(j < 0) {
            j += n;
        }

        out[i] = in[j];
    }
}

/*
 * Send a buffer to stdout.
 *
 * Second argument gives length.
 *
 * We can't just use fputs because out may contain null characters.
 */
void
ship(const char *out, int n)
{
    /* could also use fwrite */
    for(int i = 0; i < n; i++) {
        putchar(out[i]);
    }
}

/*
 * Read sequence of blocks, feed each to transpose then ship.
 */
int
main(int argc, char **argv)
{
    int n;
    int a;
    int b;
    char *in;
    char *out;
    int c;
    int i;

    if(argc != 4) {
        fprintf(stderr, "Usage: %s n a b\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);
    a = atoi(argv[2]);
    b = atoi(argv[3]);

    if(n <= 0) {
        fprintf(stderr, "%s: block size n must be positive\n", argv[0]);
        return 2;
    }

    in = malloc(n);
    assert(in);

    out = malloc(n);
    assert(out);

    i = 0;

    /* more efficient solution would use fread, but EOF is a nuisance */
    while((c = getchar()) != EOF) {
        /* write to next position in in */
        in[i++] = c;
        if(i == n) {
            /* encode and ship */
            transpose(in, out, n, a, b);
            ship(out, n);

            i = 0;
        }
    }

    if(i > 0) {
        /* pad remaining bytes with nulls and ship */
        for(; i < n; i++) {
            in[i] = '\0';
        }

        transpose(in, out, n, a, b);
        ship(out, n);
    }

    /* clean up */
    free(in);
    free(out);

    return 0;
}
