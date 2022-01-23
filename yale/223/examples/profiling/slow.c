#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <string.h>

/* concatenate n copies of src into dest */
/* returns dest */
/* caller is responsible for making dest large enough */
char *
replicate(char *dest, const char *src, int n)
{
    /* truncate dest */
    dest[0] = '\0';

    /* BAD: each call to strcat requires walking across dest */
    for(int i = 0; i < n; i++) {
        strcat(dest, src);
    }

    return dest;
}

/* like strcpy, but only copies characters at indices 0, 2, 4, ...
   from src to dest */
char *
copyEvenCharacters(char *dest, const char *src)
{
    int i;
    int j;

    /* BAD: Calls strlen on every pass through the loop */
    for(i = 0, j = 0; i < strlen(src); i += 2, j++) {
        dest[j] = src[i];
    }

    dest[j] = '\0';

    return dest;
}

/* like puts, but stops after maxChars characters */
void
putsRestricted(const char *s, int maxChars)
{
    for(int i = 0; s[i]; i++) {
        if(i >= maxChars) {
            printf("[%zu more]\n", strlen(s) - i);
            return;
        } else {
            putchar(s[i]);
        }
    }

    putchar('\n');
}

#define SMALL (10)
#define BIG (100000)
#define PATTERN "abcd"

#define BUFFER_SIZE (BIG * strlen(PATTERN) + 1)

/* how many characters to print at once */
#define MAX_CHARS (40)

int
main(int argc, char **argv)
{
    char *buffer;
    char *half;

    buffer = malloc(BUFFER_SIZE);
    half = malloc(BUFFER_SIZE);

    putsRestricted(replicate(buffer, PATTERN, SMALL), MAX_CHARS);
    putsRestricted(copyEvenCharacters(half, buffer), MAX_CHARS);

    putsRestricted(replicate(buffer, PATTERN, BIG), MAX_CHARS);
    putsRestricted(copyEvenCharacters(half, buffer), MAX_CHARS);

    free(half);
    free(buffer);

    return 0;
}
