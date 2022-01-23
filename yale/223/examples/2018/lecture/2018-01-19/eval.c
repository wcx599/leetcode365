#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>   /* for CHAR_BITS */

/* this horrible macro prints an expression and its value */
#define Eval(x) (printf("%s == %d\n", #x, (x)))

/* same thing but first argument gives format code */
#define EvalF(format, x) (printf("%s == %" #format " [%%%s]\n", #x, (x), #format))

/* This computes the number of bits in an unsigned int.
 * The sizeof operator returns the number of chars in an unsigned int,
 * then we multiply by CHAR_BIT (almost always 8) to get bits. */
#define BITS_TO_PRINT (sizeof(unsigned int) * CHAR_BIT)

void
printBits(unsigned int x)
{
    printf("%x == ", x);

    for(int position = BITS_TO_PRINT - 1; position >= 0; position--) {
        // printf("%d", (x >> position) & 0x1);
        putchar((x >> position) & 0x1 ? '1' : '0');
    }
    puts(" [printBits]");
}


int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    puts("Each line prints an expression and its value.");
    puts("Default output format is printf %d");
    puts("Other formats appear in brackets after the value.\n");

    /* evil macro version */
    Eval(2+2);

    /* nice normal version*/
    printf("2+2 == %d\n", 2+2);

    /* integer constants */
    
    /* ordinary-looking decimal values */
    Eval(12);
    Eval(-7);
    Eval(0);

    /* hexadecimal: prefix with 0x */
    Eval(0xff);
    Eval(0x10);

    /* no binary input */
    /* 1011 0110 */
    Eval(0xb6);

    /* octal (base 8): prefix with 0 */
    Eval(010);
    Eval(012);

    /* binary to octal */
    /* 1011 0110 == 010 110 110 */
    Eval(0266);

    Eval(123);
    Eval(047);   /* don't pad with leading zeroes or you will get octal */

    /* print in other formats */
    printf("0xdeadbeef == %x [%%x]\n", 0xdeadbeef);
    printf("01234 == %o [%%o]\n", 01234);

    /* floating-point values */
    printf("7.3 == %g [%%g]\n", 7.3);
    EvalF(g, 7.3);

    EvalF(g, 3.1415926);
    EvalF(g, 314e-2);
    EvalF(g, 1e217);
    EvalF(g, 1/9.0);
    EvalF(0.20g, 1/9.0);

    /* more integer constants representing ASCII characters */
    Eval('a');         /* same as 97 */
    Eval('a'+'a');     /* UGLY but legal */

    /* can specify unsigned ints with u suffix */
    Eval(97u);
     
    /* can specify long or long long with l or ll */
    EvalF(llu, -1ll);
    EvalF(llx, -1ll);

    /* arithmetic */
    /* + - * / (division) all pretty much as expected */
    Eval(2+2);
    Eval(2*2);
    Eval(2-2);
    Eval(2/2);

    EvalF(g, 2.17+3.1415);
    EvalF(g, 2.17*3.1415);
    EvalF(g, 2.17-3.1415);
    EvalF(g, 2.17/3.1415);

    /* C integer division truncates toward zero */
    Eval(3/2);
    Eval((-3)/2);
    Eval(3/-2);
    Eval(-3/-2);

    /* floating point doesn't truncate */
    EvalF(g, 3.0/2);

    /* can cast to float or double to force floating-point division */
    EvalF(0.20g, (double) 2 / 9);
    EvalF(0.20g, (float) 2 / 9);
    EvalF(0.20g, 2.0 / 9);

    /* secret 5th arithmetic operation */
    /* only works on integers */
    /* best used on unsigned integers */
    /* x % y == remainder when x / y */
    /* x % y + (x/y)*y == x */
    Eval(5 % 3);
    Eval(-5 % 3);
    Eval(5 % -3);
    Eval(-5 % -3);

    int x;  /* this is an integer variable */
    Eval(x == 2.0 / 9);
    Eval(x == 8.999 / 9);

    Eval((int) (8.999 / 9));

    EvalF(x, 0xdeadbeef >> 4);
    EvalF(08x, 0xdeadbeef >> 4);  /* %08x means print at least 8 characters and pad with zeros */
    EvalF(x, -1 >> 4);
    EvalF(x, -22811 >> 4);

    printBits(0xdeadbeef);

    EvalF(x, 0xdeadbeef >> 1);
    printBits(0xdeadbeef >> 1);

    /* comparisons */
    Eval(2 == 3);
    Eval(2 != 3);
    Eval(2 > 3);
    Eval(3 > 2);
    Eval(2 >= 2);
    Eval(2 >= 3);
    Eval(2 <= 3);

    /* ternary if/then
     *
     * The expresion
     * test ? trueCase : falseCase
     * evaluates and returns trueCase if test is nonzero and falseCase otherwise.
     *
     * This is only rarely used but can sometimes make code cleaner than using an if statement.
     */

    Eval(17 ? 23 : 45);
    Eval(0 ? 23 : 45);
    Eval(2 > 3 ? 2 : 3);

    return 0;
}
