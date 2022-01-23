#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <sys/resource.h>

// time various Fibonacci series calculators

// return user time so far in seconds
static double
userTime(void)
{
    struct rusage r;

    getrusage(RUSAGE_SELF, &r);

    return r.ru_utime.tv_sec + r.ru_utime.tv_usec / 1e6;
}

// minimum time in seconds for each test
#define MIN_TIME (0.10)

// Timing harness.
// This runs f(arg) repeatedly until at least MIN_TIME
// user time is consumed,
// then prints the result and the average time.
// Accuracy may be poor if f is very fast.
// 
// Does not attempt to subtract off overhead time.
static void
testRunTime(const char *fname, uint64_t (*f)(int), int arg)
{
    unsigned long count = 0;   // how many times we re-ran
    uint64_t result = 0;
    double end = 0;            // time at end of last test
    double start = userTime(); 

    // We will re-run until at least MIN_TIME goes by.
    // This does not give great accuracy, but it is better than nothing.
    do {
        result = f(arg);
        count++;
        end = userTime();
    } while (end - start <= MIN_TIME);

    printf("%s(%d) == %" PRIu64 " (%#.3g seconds per call)\n", 
            fname, arg, result, (end - start) / count);

    // avoid buffering
    fflush(stdout);
}

// largest value for which fib function won't overflow a uint64_t
#define MAX_FIB_ARG (93)

// exponential-time recursive implementation
static uint64_t
fibRecursive(int n)
{
    assert(n >= 0 && n <= MAX_FIB_ARG);

    if(n < 2) {
        return n;
    } else {
        return fibRecursive(n-1) + fibRecursive(n-2);
    }
}

#define NO_MEMO_ENTRY (UINT64_MAX)

// improved version with memoization
static uint64_t
fibMemoized(int n)
{
    static int tableInitialized = 0;
    static uint64_t table[MAX_FIB_ARG+1];

    assert(n >= 0 && n <= MAX_FIB_ARG);

    if(!tableInitialized) {
        for(int i = 0; i <= MAX_FIB_ARG; i++) {
            table[i] = NO_MEMO_ENTRY;
        }
        tableInitialized = 1;
    }

    if(table[n] == NO_MEMO_ENTRY) {
        if(n < 2) {
            table[n] = n;
        } else {
            table[n] = fibMemoized(n-1) + fibMemoized(n-2);
        }
    }

    return table[n];
}

// further improvement with dynamic programming
static uint64_t
fibDynamicProgramming(int n)
{
    uint64_t table[MAX_FIB_ARG+1];

    assert(n >= 0 && n <= MAX_FIB_ARG);

    table[0] = 0;
    table[1] = 1;

    for(int i = 2; i <= n; i++) {
        table[i] = table[i-1] + table[i-2];
    }

    return table[n];
}

// optimize space use
static uint64_t
fibConstantSpace(int n)
{
    assert(n >= 0 && n <= MAX_FIB_ARG);

    if(n < 2) {
        return n;
    } else {
        uint64_t r0 = 0;
        uint64_t r1 = 1;
        // r1 = fib(last)
        for(int last = 1; last < n; last++) {
            // get new value
            uint64_t r2 = r0 + r1;

            // shift everything over
            r0 = r1;
            r1 = r2;
        }

        return r1;
    }
}

#define NUM_FUNCTIONS (4)

struct namedFunction {
    const char *name;
    uint64_t (*f)(int);
};

static struct namedFunction fib[NUM_FUNCTIONS] = {
    { "fibRecursive", fibRecursive },
    { "fibMemoized", fibMemoized },
    { "fibDynamicProgramming", fibDynamicProgramming },
    { "fibConstantSpace", fibConstantSpace }
};

int
main(int argc, char **argv)
{
    int index;

    if(argc !=2 || (index = atoi(argv[1])) < 0 || index >= NUM_FUNCTIONS) {
        fprintf(stderr, "Usage: %s index, where index is one of\n", argv[0]);
        for(int i = 0; i < NUM_FUNCTIONS; i++) {
            fprintf(stderr, "%d: %s\n", i, fib[i].name);
        }
        return 2;
    }

    // run the test for each value of n
    for(int n = 0; n <= MAX_FIB_ARG; n++) {
        testRunTime(fib[index].name, fib[index].f, n);
    }

    return 0;
}
