#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "radixSort.h"

/* used internally by getLine; initial size of buffer */
#define INITIAL_LINE_SIZE (16)

/* reads a line of text terminated by newline or end-of-file and returns it */
/* returns 0 on allocation error or end-of-file at start of line */
static char *
getLine(FILE *f)
{
    int size;
    int len;
    char *line;
    int c;

    size = INITIAL_LINE_SIZE;
    len = 0;
    line = malloc(size);

    assert(line);

    for(;;) {
	/* grow the buffer if full */
	if(len >= size) {
	    size *= 2;
	    line = realloc(line, size);
	    if(line == 0) {
		free(line);
		return 0;
	    }
	}
	/* grab and parse the next character */
	c = getc(f);
	if(c == '\n') {
	    /* we are done */
	    break;
	} else if(c == EOF) {
	    if(len == 0) {
		/* end of file at start of line */
		free(line);
		return 0;
	    } else {
		/* we are done again */
		break;
	    }
	} else {
	    /* add it in */
	    line[len++] = c;
	}
    }

    /* we are done; clean up */
    /* mark end of string */
    line[len] = '\0';
    /* give up extra space in buffer */
    line = realloc(line, len + 1);
    return line;
}

#define INITIAL_LINES (16)	/* initial size of lines buffer in getlines */

/* get a bunch of lines, terminating when getline fails */
/* returns an array of the lines in order, with the number of lines stored
 * in *n */
/* returns 0 on allocation error */
/* call freeLines to free this structure */
static char **
getLines(FILE *f, int *n)
{
    int size;
    char **lines;
    char *nextLine;

    size = INITIAL_LINES;
    *n = 0;
    lines = malloc(sizeof(*lines) * size);
    if(lines == 0) return 0;

    while((nextLine = getLine(f)) != 0) {
	/* maybe grow buffer */
	if(*n >= size) {
	    size *= 2;
	    lines = realloc(lines, sizeof(*lines) * size);
	    if(lines == 0) return 0;
	}
	/* store the new line */
	lines[(*n)++] = nextLine;
    }

    /* shrink to fit */
    lines = realloc(lines, sizeof(*lines) * (*n));
    
    return lines;
}

/* free the structure returned by getLines */
static void
freeLines(char **lines)
{
    int i;

    for(i = 0; lines[i]; i++) {
        free(lines[i]);
    }

    free(lines);
}


int
main(int argc, char **argv)
{
    char **lines;
    int n;
    int i;

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    lines = getLines(stdin, &n);
    assert(lines);

    radixSort(n, (const char **) lines);

    for(i = 0; i < n; i++) {
        puts(lines[i]);
    }

    freeLines(lines);

    return 0;
}
