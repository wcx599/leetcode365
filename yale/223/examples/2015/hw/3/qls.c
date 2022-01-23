/*
 * Search for quadratic letter sequences starting with words from argv on stdin.
 *
 * A quadratic letter sequence of length n in s is a sequence of characters
 *
 *     s[c0 + c1*i + c2*i*i]
 *
 * where c0, c1, c2 are all >= 0, at least one of c1 and c2 is > 0,
 * and i ranges over 0, 1, 2, ..., n-1.
 *
 * For each QLS found, prints c0, c1, c2, and the target string to stdout.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define NUM_COEFFICIENTS (3)  /* how many coefficients to pass around */

/*
 * Return true iff we get a match in s for t with coefficients c
 *
 * Behavior is undefined if coefficients would send us off the end of s.
 */
static int
qlsMatch(const char *s, const char *t, int c[NUM_COEFFICIENTS])
{
    int i;

    for(i = 0; t[i] != '\0';  i++) {
        if(s[c[0] + c[1] * i + c[2] * i * i] != t[i]) {
            /* no match */
            return 0;
        }
    }

    return 1;
}

/* 
 * Search for quadratic letter sequences in s starting with t
 * and print results to stdout.
 */
static void
qlsSearch(const char *s, const char *t)
{
    int c[NUM_COEFFICIENTS];  /* coefficients */
    int lenS;  /* length of s */
    int lenT;  /* length of t */
    int maxI;  /* maximum value for i (this is lenT-1) */

    lenS = strlen(s);
    lenT = strlen(t);
    maxI = lenT-1;

    /* try all possible c[0] that will let us finish before lenS */
    for(c[0] = 0; c[0] + maxI < lenS; c[0]++) {
        /* if s[c[0]] isn't right, c[1] and c[2] can't fix it */
        if(s[c[0]] == t[0]) {
            /* try all feasible c[1] */
            for(c[1] = 0; c[0] + c[1] * maxI < lenS; c[1]++) {
                /* try all feasible c[2], but start at 1 if c[1] == 0 */
                for(c[2] = (c[1] == 0); c[0] + c[1] * maxI + c[2] * maxI * maxI < lenS; c[2]++) {
                    /* now see if we get a match */
                    if(qlsMatch(s, t, c)) {
                        printf("%d %d %d %s\n", c[0], c[1], c[2], t);
                    }
                }
            }
        }
    }
}

/* used internally by getContents; initial size of buffer */
#define INITIAL_BUFFER_SIZE (16)

/* 
 * Return a single string holding all characters from stdin.
 *
 * This is malloc'd data that the caller should eventually free.
 */ 
static char *
getContents(void)
{
    size_t size;
    size_t len;
    char *text;
    int c;

    size = INITIAL_BUFFER_SIZE;
    len = 0;

    text = malloc(size);
    assert(text);

    while((c = getchar()) != EOF) {
	/* grow the buffer if full */
	if(len >= size) {
	    size *= 2;
	    text = realloc(text, size);
            assert(text);
	}

        text[len++] = c;
    }

    /* cleanup */
    text = realloc(text, len+1);
    assert(text);

    text[len] = '\0';

    return text;
}


int
main(int argc, char **argv)
{
    int i;
    char *s;

    s = getContents();

    for(i = 1; i < argc; i++) {
        qlsSearch(s, argv[i]);
    }

    free(s);

    return 0;
}
