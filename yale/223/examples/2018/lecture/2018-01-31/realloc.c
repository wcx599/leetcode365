/* demonstrates use of realloc to deal with objects
 * of unpredictable size. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DEFAULT_SIZE (8)

/* read the entire contents of stdin 
 * and return as malloc'd string */
char *
getContents(void)
{
    int c;
    char *a;   // stuff so far
    size_t top = 0;  // first unused position
    size_t size = DEFAULT_SIZE;  // actual size of a in chars

    /* allocate initial buffer */
    a = malloc(size);
    assert(a);

    while((c = getchar()) != EOF) {
        while(size < top + 2) {
            /* double size and realloc */
            size *= 2;

            printf("calling realloc to increase size to %zu\n", size);

            a = realloc(a, size);
            assert(a);
        }

        a[top] = c;
        top++;
    }

    a[top] = '\0';
    top++;

    size = top;

    printf("calling realloc to decrease size to %zu\n", size);

    a = realloc(a, size);

    return a;
}

int
main(int argc, char **argv)
{
    char *buffer;

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    buffer = getContents();

    /* unlike puts, fputs does not write an extra newline */
    fputs(buffer, stdout);

    free(buffer);

    return 0;
}
