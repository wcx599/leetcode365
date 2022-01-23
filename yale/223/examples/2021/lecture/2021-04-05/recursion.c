#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

// print all ints in range [start, end)
// using recursion

// idea: print [start, end-1) first, then print end-1
void
printRange1(int start, int end)
{
    printf("printRange1(%d, %d)\n", start, end);

    if(start < end) {
        printRange1(start, end-1);
        printf("%d\n", end-1);
    }
}

// new idea: print start, the print [start+1, end)
void
printRange2(int start, int end)
{
    printf("printRange2(%d, %d)\n", start, end);

    if(start < end) {
        printf("%d\n", start);

        // tail recursion - can be eliminated
        printRange2(start+1, end);
    }
}

// new idea: print start, the print [start+1, end)
void
printRange2a(int start, int end)
{
top:
    printf("printRange2a(%d, %d)\n", start, end);

    if(start < end) {
        printf("%d\n", start);

        // tail recursion - can be eliminated
        start = start + 1;
        goto top;
    }
}

// new idea: print start, the print [start+1, end)
// idiomatic version with no tail recursion
void
printRange2b(int start, int end)
{
    while(start < end) {
        printf("%d\n", start);

        // tail recursion - can be eliminated
        start = start + 1;
    }
}

// what if we split range in half?
void
printRangeSplit(int start, int end)
{
    int mid = (start + end) / 2;

    printf("printRangeSplit(%d, %d)\n", start, end);

    if(start < end) {
        if(end - start == 1) {
            printf("%d\n", start);
        } else {
            printRangeSplit(start, mid);
            printRangeSplit(mid, end);
        }
    }
}

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    // printRange1(0, 10);
    printRange2(0, 6);
    printRange2a(0, 6);
    printRange2b(0, 6);
    printRangeSplit(0, 7);

    return 0;
}
