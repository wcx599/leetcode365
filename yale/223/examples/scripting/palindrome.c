#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Palindrome detector.
 *
 * For each line of the input, prints PALINDROME if it is a palindrome
 * or the index of the first non-matching character otherwise.
 *
 * Note: does not handle lines containing nulls.
 */

/* read a line of text from stdin
 * and return it (without terminating newline) as a freshly-malloc'd block.
 * Caller is responsible for freeing this block.
 * Returns 0 on error or EOF.
 */
char *
getLine(void)
{
    char *line;		/* line buffer */
    int n;		/* characters read */
    int size; 		/* size of line buffer */
    int c;

    size = 1;
    line = malloc(size);
    if(line == 0) return 0;
    
    n = 0;

    while((c = getchar()) != '\n' && c != EOF) {
	while(n >= size - 1) {
	    size *= 2;
	    line = realloc(line, size);
	    if(line == 0) return 0;
	}
	line[n++] = c;
    }

    if(c == EOF && n == 0) {
	/* got nothing */
	free(line);
	return 0;
    } else {
	line[n++] = '\0';
	return line;
    }
}

#define IS_PALINDROME (-1)

/* returns IS_PALINDROME if s is a palindrome,
 * or index of first unmatched character otherwise. */
int 
testPalindrome(const char *s)
{
    int n;	/* length of s */
    int i;

    n = strlen(s);

    /* we only have to check up to floor(n/2) */
    for(i = 0; i < n/2; i++) {
	if(s[i] != s[n-1-i]) {
	    return i;
	}
    }
    /* else */
    return IS_PALINDROME;
}

int
main(int argc, char **argv)
{
    char *line;
    int mismatch;

    while((line = getLine()) != 0) {
	mismatch = testPalindrome(line);
	if(mismatch == IS_PALINDROME) {
	    puts("PALINDROME");
	} else {
	    printf("%d\n", mismatch);
	}

	free(line);
    }

    return 0;
}

	
