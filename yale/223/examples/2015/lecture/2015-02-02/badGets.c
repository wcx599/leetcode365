#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NAME_LENGTH (2)

#define INITIAL_LINE_LENGTH (2)

/* return a freshly-malloc'd line with next line of input from stdin */
char *
getLine(void)
{
    char *line;
    int size;   /* how much space do I have in line? */
    int length; /* how many characters have I used */
    int c;

    size = INITIAL_LINE_LENGTH;
    line = malloc(size);
    assert(line);

    length = 0;

    while((c = getchar()) != EOF && c != '\n') {
        if(length >= size-1) {
            /* need more space! */
            size *= 2;

            /* make length equal to new size */
            /* copy contents if necessary */
            line = realloc(line, size);
        }

        line[length++] = c;
    }

    line[length] = '\0';

    return line;
}

int
main(int argc, char **argv)
{
    int x = 12;
    /* char name[NAME_LENGTH]; */
    char *line;
    int y = 17;

    puts("What is your name?");

    /* gets(name); */
    /* scanf("%s\n", name); */
    /* fgets(name, NAME_LENGTH, stdin); */
    line = getLine();
    
    printf("Hi %s!  Did you know that x == %d and y == %d?\n", line, x, y);

    free(line);

    return 0;
}
