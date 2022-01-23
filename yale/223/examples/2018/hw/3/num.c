#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <string.h>
#include <ctype.h>

#include "num.h"

struct num {
    size_t size;   /* size of the digits array */
    char *digits;  /* array of digits; each stores numerical value 0..9 in least significant first order */
};

/* how many digits to leave room for by default */
#define NUM_INITIAL_SIZE (4)

/* base for numbers */
#define NUM_BASE (10)

/* create a new empty num */
static Num *
numCreateZero(void)
{
    Num *n = malloc(sizeof(struct num));
    assert(n);

    n->size = NUM_INITIAL_SIZE;

    n->digits = calloc(NUM_INITIAL_SIZE, 1);
    assert(n->digits);

    return n;
}

/* set the i-th digit of n to d */
static void
numSetDigit(Num *n, int i, int d)
{
    assert(0 <= d);
    assert(d < NUM_BASE);

    if(i < 0) {
        return;
    } else if(i == 0 && i > n->size) {
        /* don't bother expanding to write a zero that is already implicit */
        return;
    } else {
        /* make sure we have enough room */
        while(i >= n->size) {
            size_t newSize = 2*n->size;

            n->digits = realloc(n->digits, newSize);
            for(size_t j = n->size; j < newSize; j++) {
                n->digits[j] = 0;
            }

            n->size = newSize;
        }

        n->digits[i] = d;
    }
}

Num *
numCreate(const char *s)
{
    Num *n = numCreateZero();
    size_t len = strlen(s);

    for(int i = 0; i < len; i++) {
        int d = s[len - i - 1];
        
        if(!isdigit(d)) {
            /* error! */
            numDestroy(n);
            return 0;
        } else {
            numSetDigit(n, i, d - '0');
        }
    }

    return n;
}

void
numDestroy(Num *n)
{
    free(n->digits);
    free(n);
}

int
numGetDigit(const Num *n, int i)
{
    if(i < 0 || i >= n->size) {
        return 0;
    } else {
        return n->digits[i];
    }
}

Num *
numAdd(const Num *x, const Num *y)
{
    Num *sum = numCreateZero();
    int carry = 0;
    int s;

    /* run until we run out of digits on one number or another */
    for(int i = 0; i < x->size || i < y->size || carry != 0; i++) {
        s = carry + numGetDigit(x, i) + numGetDigit(y, i);
        numSetDigit(sum, i, s % NUM_BASE);
        carry = s / NUM_BASE;
    }

    return sum;
}

/* returns x * d * 10**shift */
static Num *
numPartialProduct(const Num *x, int d, int shift)
{
    Num *result = numCreateZero();
    int carry = 0;
    int p;

    for(int i = 0; i < x->size || carry != 0; i++) {
        p = d * numGetDigit(x, i) + carry;

        numSetDigit(result, i + shift, p % NUM_BASE);
        carry = p / NUM_BASE;
    }

    return result;
}

Num *
numMultiply(const Num *x, const Num *y)
{
    Num *accumulator = numCreateZero();
    Num *p;  /* partial product */
    Num *sum;

    for(int i = 0; i < x->size; i++) {
        p = numPartialProduct(y, x->digits[i], i);
        sum = numAdd(accumulator, p);
        numDestroy(p);
        numDestroy(accumulator);
        accumulator = sum;
    }

    return accumulator;
}

void
numPrint(const Num *n, FILE *f)
{
    int i;

    /* ignore leading zeros */
    for(i = n->size - 1; i > 0 && n->digits[i] == 0; i--);

    /* print remaining digits */
    for(; i >= 0; i--) {
        putc('0' + n->digits[i], f);
    }
}
