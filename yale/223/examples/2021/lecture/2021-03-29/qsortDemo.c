#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#define NUM_STRINGS (3)
#define NUM_NUMS (5)

static int
stringCompare(const void *a, const void *b)
{
    return strcmp(*((const char **) a), *((const char **) b));
}

static int
intCompare(const void *a, const void *b)
{
    return *((const int *) a) - *((const int *) b);
}

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    // here are some arrays to sort
    const char *strings[NUM_STRINGS] = { "cauliflower", "boo", "a" };
    int nums[NUM_NUMS] = { 5, 1, 4, 3, 2 };

    // sort arrays here
    qsort(strings, NUM_STRINGS, sizeof(const char *), stringCompare);
    qsort(nums, NUM_NUMS, sizeof(int), intCompare);

    for(int i = 0; i < NUM_STRINGS; i++) {
        puts(strings[i]);
    } 

    putchar('\n');

    for(int i = 0; i < NUM_NUMS; i++) {
        printf("%d\n", nums[i]);
    }

    return 0;
}
