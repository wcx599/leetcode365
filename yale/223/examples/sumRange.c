#include <stdio.h>    /* This is needed to get the declarations of fprintf and printf */
#include <stdlib.h>   /* This is needed to get the declaration of atoi */

/* Return the sum of all integers i
 * such that start <= i and i < end. */
int
sumRange(int start, int end)
{
    int i;    /* loop variable */
    int sum;  /* sum of all values so far */

    /* a mathematician would use a formula for this,
     * but we are computer programmers! */
    sum = 0;

    /* The three parts of the header for this loop mean:
     * 1. Set i to start initially.
     * 2. Keep doing the loop as long as i is less than end.
     * 3. After each iteration, add 1 to i.
     */
    for(i = start; i < end; i++) {
        sum += i;  /* This adds i to sum */
    }

    /* This exits the function immediately,
     * sending the value of sum back to the caller. */
    return sum;
}

int
main(int argc, char **argv)
{
    int start;    /* initial value in range */
    int end;      /* one past the last value in the range */

    /* This tests for the wrong number of arguments.
     * The != operator returns true (1) if its arguments are not equal,
     * and false (0) otherwise.
     * Note that the program name itself counts as an argument
     * (which is why we want the argument count to be 3)
     * and appears in position 0 in the argument vector
     * (which means we can get it using argv[0]). */
    if(argc != 3) {
        fprintf(stderr, "Usage: %s\n start end", argv[0]);
        return 1;
    }

    /* Convert start and end positions from strings to ints */
    start = atoi(argv[1]);
    end = atoi(argv[2]);

    /* Call sumRange and print the result */
    printf("sumRange(%d, %d) = %d\n", start, end, sumRange(start, end));

    return 0;
}
