#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

/* compute longest common subsequence of argv[1] and argv[2] */

/* computes longest common subsequence of x and y, writes result to lcs */
/* lcs should be pre-allocated by caller to 1 + minimum length of x or y */
void
longestCommonSubsequence(const char *x, const char *y, char *lcs)
{
    int xLen;
    int yLen;
    int i;             /* position in x */
    int j;             /* position in y */

    xLen = strlen(x);
    yLen = strlen(y);

    /* best choice at each position */
    /* length gives length of LCS for these prefixes */
    /* prev points to previous substring */
    /* newChar if non-null is new character */
    struct choice {
        int length;
        struct choice *prev;
        char newChar;
    } best[xLen][yLen];

    for(i = 0; i < xLen; i++) {
        for(j = 0; j < yLen; j++) {
            /* we can always do no common substring */
            best[i][j].length = 0;
            best[i][j].prev = 0;
            best[i][j].newChar = 0;

            /* if we have a match, try adding new character */
            /* this is always better than the nothing we started with */
            if(x[i] == y[j]) {
                best[i][j].newChar = x[i];
                if(i > 0 && j > 0) {
                    best[i][j].length = best[i-1][j-1].length + 1;
                    best[i][j].prev = &best[i-1][j-1];
                } else {
                    best[i][j].length = 1;
                }
            }

            /* maybe we can do even better by ignoring a new character */
            if(i > 0 && best[i-1][j].length > best[i][j].length) {
                /* throw away a character from x */
                best[i][j].length = best[i-1][j].length;
                best[i][j].prev = &best[i-1][j];
                best[i][j].newChar = 0;
            }

            if(j > 0 && best[i][j-1].length > best[i][j].length) {
                /* throw away a character from x */
                best[i][j].length = best[i][j-1].length;
                best[i][j].prev = &best[i][j-1];
                best[i][j].newChar = 0;
            }

        }
    }

    /* reconstruct string working backwards from best[xLen-1][yLen-1] */
    int outPos;        /* position in output string */
    struct choice *p;  /* for chasing linked list */

    outPos = best[xLen-1][yLen-1].length;
    lcs[outPos--] = '\0';

    for(p = &best[xLen-1][yLen-1]; p; p = p->prev) {
        if(p->newChar) {
            assert(outPos >= 0);
            lcs[outPos--] = p->newChar;
        }
    }
}

int
main(int argc, char **argv)
{
    if(argc != 3) {
        fprintf(stderr, "Usage: %s string1 string2\n", argv[0]);
        return 1;
    }

    char output[strlen(argv[1]) + 1];

    longestCommonSubsequence(argv[1], argv[2], output);

    printf("\"%s\" (%zu characters)\n", output, strlen(output));

    return 0;
}
