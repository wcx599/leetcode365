#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

// print an int-valued expression and its value
#define Show(x) (printf("%20s == %d\n", #x, (x)))

// print an pointer-valued expression and its value
#define ShowP(x) (printf("%20s == %p\n", #x, (void *) (x)))

// swap values of *x and *y
void
swap(int *x, int *y)
{
    int temp;

    temp = *x;
    *x = *y;
    *y = temp;
}

// print contents of the array
void
printArray(size_t n, const int *a)
{
    for(size_t i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    putchar('\n');
}

// fill with 1 through n
void
iota(size_t n, int *a)
{
    for(size_t i = 0; i < n; i++) {
        a[i] = i+1;
    }
}

// compute sum of a
int
sum(size_t n, const int a[])
{
    int accum = 0;
    for(size_t i = 0; i < n; i++) {
        accum += a[i];
    }

    return accum;
}

#define N (4) // size of my array

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    int x = 2;  // an int variable
    int *p = &x; // pointer to x

    Show(x);
    ShowP(p);
    Show(*p = 35);
    Show(x);
    ShowP(p);

    // let's do another variable
    int y = 12;
    Show(y);
    ShowP(p = &y);
    Show(*p);
    Show(*p = 137);
    Show(x);
    Show(y);
    ShowP(p);

    puts("swap(y, x);");
    swap(&y, &x);
    Show(x);
    Show(y);

    int b[N];
    ShowP(b);
    printArray(N, b);
    iota(N, b);
    ShowP(b);
    printArray(N, b);

    Show(sum(N, b));
    Show(sum(N-1, b+1));
    printArray(N-1, b+1);

    // I think y is stored at b+4
    // (not guaranteed)
    Show(y);
    Show(b[4] = 735);  // by running off the end of b, I change something else :(
    Show(y);

    // maybe this will segfault
    Show(b[1919129] = 12);

    return 0;
}
