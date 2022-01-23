#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <string.h>

// demo program for qsort

#define DIE_SIZE (6)

void
printArray(const int *a, int n)
{
    for(int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    putchar('\n');
}

void
printStringArray(const char **a, int n)
{
    for(int i = 0; i < n; i++) {
        puts(a[i]);
    }
}


// given two pointers to ints, compare them
int
intCompare(const void *a, const void *b)
{
    return *((const int *) a) - *((const int *) b);
}

int
stringCompare(const void *a, const void *b)
{
    return strcmp(*((const char **) a), *((const char **) b));
}

int
main(int argc, char **argv)
{
    int n;  // how many samples to generate
    int *a; // array of samples

    srand(1);  // fix seed so we get consistent behavior

    if(argc != 2) {
        fprintf(stderr, "Usage: %s number-of-samples\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);
    a = calloc(n, sizeof(int));
    assert(a);

    // generate n random values
    for(int i = 0; i < n; i++) {
        // roll 1d6
        a[i] = ((unsigned int) rand()) % DIE_SIZE + 1;
    } 

    // and print them out
    printArray(a, n);

    // now sort them
    qsort((void *) a, n, sizeof(int), intCompare);

    // and print them out
    printArray(a, n);

    const char *strings[] = { "this", "is", "a", "test" };

    qsort((void *) strings, 4, sizeof(char *), stringCompare);
    printStringArray(strings, 4);


    free(a);

    return 0;
}
