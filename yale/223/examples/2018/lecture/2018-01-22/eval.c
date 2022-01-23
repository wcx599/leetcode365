#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>   /* for CHAR_BITS */

/* this horrible macro prints an expression and its value */
#define Eval(x) (printf("%3d: %s == %d\n", __LINE__, #x, (x)))

/* same thing but first argument gives format code */
#define EvalF(format, x) (printf("%3d: %s == %" #format " [%%%s]\n", __LINE__, #x, (x), #format))

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    puts("Each line prints a line number, an expression, and its value.");
    puts("Default output format is printf %d.");
    puts("Other formats appear in brackets after the value.\n");

    Eval(2+2);

    int x = 37;

    Eval(x);
    Eval(x*3);

    /* assignment operator = sets LHS to value of RHS */
    /* returns new value */
    Eval(x = 12);
    Eval(x);

    /* can combine assignment with other operators, does update */
    Eval(x += 3);  // add 3 to x, store in x
    Eval(x = x + 3);
    Eval(x *= 2);  // x = x*2
    Eval(x <<= 4); // x = x << 4

    /* ++ increments a variable, -- decrements it */
    /* return value depends on which side of variable name operator appears on */

    /* pre-increment: inc first, return value */
    Eval(x=3);
    Eval(++x);   // pre-increment
    Eval(x);
    Eval(x++);   // post-increment
    Eval(x);

    /* -- same thing but decrements */
    Eval(x=3);
    Eval(--x);   // pre-decrement
    Eval(x);
    Eval(x--);   // post-decrement
    Eval(x);

    /* this has horrible unpredictable effects ☹ */
    int y;

    Eval(x = 3);
    Eval(y = ++x + ++x);

    Eval(x = 3);
    Eval(y = x);
    Eval(y++);
    Eval(x);

    /* statements */

    /* simplest form: expression terminated by ; */
    x = 3;
    puts("hi there");
    y = 2+2;

    /* compound statements for control flow: */

    /* if statement with else */
    if(x > 2) {
        /* do this if true */
        puts("BIG!");
    } else {
        puts("small");
    }

    /* without else */
    if(x > 2) {
        puts("BIG!");
    }
    /* otherwise do nothing */

    if(2 + 2 == 5) {
        /* not called */
        abort();
    }

    if(x < 0) {
        puts("negative");
    } else if(x == 0) {
        puts("zero");
    } else {
        puts("positive");
    }

    /* loops: do something more than once */
    x = 0;

    /* like if: runs test, executes body if test is true,
     * but then does it again */
    while(x < 4) {
        Eval(x);
        x++;
    }

    /* do..while puts test at end, redoes loop if test is true */
    x = 0;

    do {
        x++;
        Eval(x);
    } while(x < 5);

    x = 23;
    do {
        x++;
        Eval(x);
    } while(x < 5);
    

    /* for loop: syntactic sugar for while
     * that puts all loop logic at the top
     *
     * for(initial stuff; test; update) { ... }
     */

    for(int i = 0; i < 5; i++) {
        Eval(i);
    }

    /* while version */
    int i = 0;

    while(i < 5) {
        Eval(i);
        i++;
    }

    /* omit initialization */
    for(; i < 10; i += 2) {
        Eval(i);
    }

    for(int i = 0; i < 5; i++) {
        /* only works on integer types */
        switch(i) {
            case 0:
                puts("zero!");
                break;
            case 1:
                puts("one!");
                break;
            default:
                puts("MANY");
                break;
        }
    }
        



    return 0;
}
