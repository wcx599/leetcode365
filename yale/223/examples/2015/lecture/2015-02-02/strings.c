#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/* generate a random string */
/* of length 0 to n-1, with characters from start to end-1 */
/* puts it in s */
void
generateRandomString(int n, int start, int end, char *s)
{
    int i;
    int length;

    /* rand gives randomish number between 0 and RAND_MAX */
    length = rand() % n;

    for(i = 0; i < length; i++) {
        s[i] = start + rand() % (end - start);
    }

    /* don't forget the final '\0' character */
    s[length] = '\0';
}

/* compute the length of a string, not including final NUL */
int
myStrlen(const char *s)
{
    int i;

    for(i = 0; s[i] != '\0'; i++);

    return i;
}

/* copies characters in src to dest */
void
myStrcpy(char *dest, const char *src)
{
    char *origDest;

    origDest = dest;

    while((*dest++ = *src++)) {
        printf("origDest(%p) = %s, dest(%p) = %s, src(%p) = %s\n", origDest, origDest, dest, dest, src, src);
    }
}

/* more readable version of myStrcpy */
void
myStrcpyReadable(char *dest, const char *src)
{
    int i;

    for(i = 0; src[i] != '\0'; i++) {
        dest[i] = src[i];
    }

    dest[i] = '\0';
}

/* less readable version of myStrcpy */
void
myStrcpyLessReadable(char *dest, const char *src)
{
    int i;

    i = 0;
    do {
        dest[i] = src[i];
    } while(src[i++] != '\0');
}


#define NUMBER_OF_SAMPLES (10)
#define LENGTH (8)
#define START ('a')
#define END ('z'+1)

int
main(int argc, char **argv)
{
    int i;
    char buf[LENGTH];
    char dest[LENGTH];

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    for(i = 0; i < NUMBER_OF_SAMPLES; i++) {
        generateRandomString(LENGTH, START, END, buf);

        printf("myStrlen(%s) == %d\n", buf, myStrlen(buf));
        assert(myStrlen(buf) == strlen(buf));

        myStrcpy(dest, buf);
        printf("dest = %s\n", dest);
        assert(strcmp(dest, buf) == 0);

        myStrcpyReadable(dest, buf);
        assert(strcmp(dest, buf) == 0);

        myStrcpyLessReadable(dest, buf);
        assert(strcmp(dest, buf) == 0);
    }

    return 0;
}
