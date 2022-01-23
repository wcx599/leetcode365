#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#include "nums.h"
#include "tester.h"

static void sum_helper(int i, void *f_data)
{
    *((int *) f_data) += i;
}

int
main(int argc, char **argv)
{
    Nums nums;
    int sum;
    int *contents;
    int *p;
    int i;

    tester_init();

    TRY { nums = nums_create(100); } ENDTRY;
    TEST(nums_contains(nums, -1), 0);
    TEST(nums_contains(nums, 0), 1);
    TEST(nums_contains(nums, 1), 1);
    TEST(nums_contains(nums, 98), 1);
    TEST(nums_contains(nums, 99), 1);
    TEST(nums_contains(nums, 100), 0);

    sum = 0;
    contents = nums_contents(nums);
    for(p = contents; *p != -1; p++) {
        sum += *p;
    }
    free(contents);
    TEST(sum, 4950);

    sum = 0;
    for(i = nums_first(nums); !nums_done(nums, i); i = nums_next(nums, i)) {
        sum += i;
    }
    TEST(sum, 4950);

    sum = 0;
    nums_foreach(nums, sum_helper, (void *) &sum);
    TEST(sum, 4950);
    tester_report(stdout, argv[0]);
    return tester_result();
}
