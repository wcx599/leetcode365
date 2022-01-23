#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <limits.h> // for CHAR_BIT and INT_MAX
#include <ctype.h>  // for isprint()

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

void
printBits(unsigned int x)
{
    for(int i = CHAR_BIT * sizeof(int) - 1; i >= 0; i--) {
        putchar(x & (1 << i) ? '1' : '0');
        // add a space after each byte
        if(i % CHAR_BIT == 0) {
            putchar(' ');
        }
    }
}

// Fancy int printer
void
showInt(const char *label, int x)
{
    // print out the bits
    printBits(x);

    // print out hex, decimal, char (if printable), label
    printf(" %08x %12d %c %s\n", x, x, isprint((char) x) ? x : ' ', label);
}

#define FLOAT_SIGN (31)
#define FLOAT_EXPONENT_BITS (8)
#define FLOAT_MANTISSA_BITS (23)

// helper so we don't have to keep writing this expression
void
printBit(unsigned int x, int position)
{
    putchar(x & (1 << position) ? '1' : '0');
}

// print float bits
// first bit is sign, then 8 bits of exponent, then 23 of mantissa
void
printFloatBits(float f)
{
    // the pointer hackery avoids numeric conversion
    unsigned int x = *((unsigned int *) &f);

    int i = FLOAT_SIGN;

    printBit(x, i--);

    putchar(' ');

    for(int count = 0; count < FLOAT_EXPONENT_BITS; count++) {
        printBit(x, i--);
    }

    putchar(' ');

    for(int count = 0; count < FLOAT_MANTISSA_BITS; count++) {
        printBit(x, i--);
    }
}


// Fancy float printer
void
showFloat(const char *label, float f)
{
    // print out the bits
    printFloatBits(f);

    // print floating point value and label
    printf(" %8g %s\n", f, label);
}

// Use #x preprocessor magic to capture source code of an expression
#define Show(x) showInt(#x, (x))
#define ShowFloat(f) showFloat(#f, (f))

// to be used later
#define DENOMINATOR (1337)

int
main(int argc, char **argv)
{
    // scope -- where the variable is visible
    // for local variables, only visible in same function
    // extent -- how long the variable lives
    // for local variables, extent = lifetime of function call
    int i;  // <- this is an int variable, 32 bits, signed by default

    i = 2; // store 2 in i
    i = i + 7;  // on RHS, fetches the value of i

    // can also have variables local to blocks
    {
        // scope limited to inside these braces
        // extent == function lifetime
        int j;

        j = 5;
        printf("%d\n", j);
    }

    // general pattern for a variable declaration:
    //
    // type name [= initial value];
    //
    // type = int/char/unsigned long long
    //
    // name = any sequence of alphanumeric chars or _
    // alphanumeric = a..z A..Z 0..9
    //
    // must start with letter or _
    //
    int _________a____; // <--- kind of a stupid name
    int _; // <-- sometimes used for a dummy variable that doesn't get used

    // note: these variables are not initialized
    // so have arbitrary initial values!

    _________a____ = 37;
    _ = _________a____;

    printf("_ == %d\n", _);

    // compute sum of 1 to 10
    int sum = 0;   // initialized to 0; RHS is any expression

    // for statement allows a variable declaration in initializer expression
    // variable is local to for statement and its body (limited scope)
    for(int i = 1; i <= 10; i++) {
        sum = sum + i;
    }

    printf("sum == %d\n", sum);

    // good variable names vs bad variables names
    // ideal variable name: short, memorable, and says what variable does
    int numberOfElephants = 0;   // how many elephants do we have?
    int numElphts = 0;    // not so good

    // avoid the temptation to abbreviate!
    // most editors will let you complete variable names
    int totalAnimals = numElphts + numberOfElephants;
    printf("%d\n", totalAnimals);

    // exception: conventional variable names for loops and such
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d %d\n", i, j);
        }
    }


    // new topic: floating-point computation
    // idea: represent real numbers as approximate values
    // represented in binary
    float badPi = 3.14;    // 32 bits of space

    // float representation
    //  1 sign bit
    //  8 exponent bits
    // 23 mantissa bits
    //
    // value = <sign +-1> * (1 + mantissa * 2^-23) * 2^(exponent - 127)
    //
    // idea: mantissa gives 23 bits of precision
    //
    // exponent shifts range of precision to where it's most useful
    //
    // good for representing real-world quantities, always have some error
    // (probably bigger than round-off error from only using 23 bits)
    
    ShowFloat(0.0);
    ShowFloat(1.0);
    ShowFloat(2.0);
    ShowFloat(4.0);

    printf("%g\n", badPi);

    ShowFloat(1e15);  // 1.0 * 10^15
    ShowFloat(1e15+1);  // 1.0 * 10^15 + 1

    Show(1/3);  // int version
    ShowFloat(1/3);  // still int version, gets converted to float before printing
    ShowFloat(1.0/3); // float version

    float oneThird = 1 / 3.0; // another float version

    ShowFloat(oneThird + oneThird + oneThird);

    // automated type conversion
    // int -> float, produces the closest float in value
    //
    float three = 1 + 2;  // RHS is int, gets converted to 3.0

    ShowFloat(three);

    float badOneThird = 1 / 3;  // RHS is int, gets 0 -> 0.0
    ShowFloat(badOneThird);

    // can do explicit version using cast
    ShowFloat(((float) 1) / 3);

    int x = 5;

    ShowFloat((float) x / 3);

    // other direction happens on assignment or explicit cast,
    // rounds toward zero
    int rounded = 1.5;
    int roundedUp = -1.5;

    Show(rounded);
    Show(roundedUp);

    // round-off error can accumulate
    float inverseDenominator = 1.0 / DENOMINATOR;

    float denominatorSum = 0.0;

    // add up inverseDenominator DENOMINATOR times
    for(int i = 0; i < DENOMINATOR; i++) {
        denominatorSum = denominatorSum + inverseDenominator;
    }

    ShowFloat(inverseDenominator);
    ShowFloat(denominatorSum);

    // using double instead may help
    // double = 64-bit float, more exponent and mantissa bits
    // ==> more precision, though still not perfect
    double doubleInverseDenominator = 1.0 / DENOMINATOR;

    printf("doubleInverseDenominator == %g\n", doubleInverseDenominator);

    // add up doubleInverseDenominator DENOMINATOR times
    double doubleDenominatorSum = 0.0;
    for(int i = 0; i < DENOMINATOR; i++) {
        doubleDenominatorSum = doubleDenominatorSum + doubleInverseDenominator;
    }

    printf("doubleDenominatorSum == %g\n", doubleDenominatorSum);

    Show(doubleDenominatorSum == 1.0);
    printf("%g\n", doubleDenominatorSum - 1.0);

    // error values turn into NaN or +-Inf
    ShowFloat(0.0 / 0.0);
    ShowFloat(1.0 / 0.0);
    ShowFloat(-1.0 / 0.0);

    // is inf + -inf 0?
    ShowFloat(-1.0 / 0.0 + 1.0 / 0.0);

    // what about inf * 0
    ShowFloat((1.0 / 0.0) * 0.0);

    // fancy assignment operators
    //
    // for each binary operation op, there is an assignment operator
    //
    // op=
    //
    // that is equivalent to
    //
    // x = x op y
    //
    // sum += 1;
    //
    // same as
    //
    // sum = sum + 1;
    //
    // (except on top, sum only evaluated once)

    // here is a loop that prints out powers of 2
    for(unsigned int i = 1; i != 0; i *= 2) {
        Show(i);
    }
    
    puts("=====");

    // here is a loop that shifts left by 3 bits
    for(unsigned int i = 5; i != 0; i <<= 3) {
        Show(i);
    }

    // assignment operators have value
    int a;
    int b;
    int c;

    // a = (b = c = 37) equivalent to a = (b = (c = 37))
    a = b = c = 37;

    printf("%d %d %d\n", a, b, c);

    /*
    // usually only used in this idiom
    // note: use int here to allow for EOF == -1
    //
    // type control-D on terminal to send EOF
    int cc;
    while((cc = getchar()) != EOF) {
        putchar(cc);
    }
    */

    // special assignment operators for inc and dec
    int v = 0;

    // four ways to add 1 to v
    v = v + 1;
    v += 1;
    v++;     // postincrement
    ++v;     // preincrement

    Show(v);
    Show(v++);   // value returned by expression == old value of v
    Show(v);     // print value so we can see what happened
    Show(++v);   // value returned by expression == new value of v
    Show(v);

    // order of side-effects is not specified
    // ==> avoid multiple side-effects same expression
    Show(v++ + v++);

    // there is also --
    Show(v=0);
    Show(v--);
    Show(v);
    Show(--v);
    Show(v);

    // these are defined in limits.h
    Show(INT_MAX);
    Show(INT_MIN);

    return 0;
}
