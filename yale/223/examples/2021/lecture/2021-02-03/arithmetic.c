#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <limits.h> // for CHAR_BIT
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

// Fancy float printer
void
showFloat(const char *label, float f)
{
    // print out the bits
    // the pointer hackery avoids numeric conversion
    unsigned int *p = (unsigned int *) &f;
    printBits(*p);

    // print floating point value and label
    printf("%g %s\n", f, label);
}

// Use #x preprocessor magic to capture source code of an expression
#define Show(x) showInt(#x, (x))
#define ShowFloat(f) showFloat(#f, (f))

int
main(int argc, char **argv)
{
    // constructing int values
    // type in decimal
    Show(0);
    Show(137);

    // - means negative
    Show(-37);
    Show(37);
    Show(-37 + 37);

    // 0x prefix means hexadecimal
    Show(0x55555555);
    Show(0xfedcba98);
    Show(0xbad);

    // 0 prefix means octal (3 bits per digits, 0..7 digits)
    // watch out for adding 0 by accident!
    Show(0123);
    Show(012);

    // character in single quotes == ASCII numeric value
    // these are just ints!
    Show('a');
    Show('a'*'a');
    Show(97*97);

    // Some Unicode support, but won't fit in a char
    // and will produce warnings
    Show('∑');
    Show('ω');
    Show('☺');

    // Unicode in comments is fine: αβξ
 
    // Arithmetic operations
    // Usual operations: + - * /
    Show(1+2);
    Show(1-2);
    Show(2*3);

    // division always truncates toward 0
    Show(5/3);
    Show((-5)/3);
    Show(6/3);
    Show(8/3);

    // % gives remainder
    Show(5 % 3);
    Show((-5) % 3);
    Show(6 % 3);
    Show(8 % 3);

    // test for odd
    Show(5 % 2);
    Show(4 % 2);

    // order of operations: * / % bind tighter than + -
    Show(2*3+4);
    Show(2+3*4);

    // association left-to-right
    Show(2-3-4);
    Show((2-3)-4);
    Show(2-(3-4));

    // Boolean operations, return 0 (false) or 1 (true)
    Show(2 > 3);
    Show(3 > 2);
    Show((2 > 1) * 5);

    Show(1 < 2);
    Show(1 <= 1);
    
    Show(3 >= 2);

    Show(-3 >= 0);

    // be careful about signed vs unsigned
    Show((unsigned int) -3 >= 0);

    // lower precedence than arithmetic
    Show(2+3 > 5);
    Show(2+(3 > 5));

    // equality is ==
    // be careful not to use = !!!!!!
    int x;

    Show(x = 5);  // assigns 5 to x, returns value of x
    Show(x == 5); // tests if x is equal to 5

    // don't do this
    if(x = 3) {
        puts("Hey! x is equal to 3!");
    }

    // right version
    if(x == 4) {
        puts("Hey! x is equal to 4!");
    }

    // inequality !=
    Show(2 != 3);
    Show(2 != 2);

    // can also use ! by itself
    // !0 -> 1, !(anything else) -> 0
    Show(!(2 > 3));
    Show(!5);

    // !! normalizes a true/false value to 1/0
    Show(!!5);
    Show(5 != 0); // less confusing

    // bitwise operations
    // treat an int as a 32-bit value
    // apply Boolean operations to matching bits
    Show(0xf5);
    Show(0x5f);
    Show(0xf5 & 0x5f); // bitwise AND
    Show(0xf5 | 0x5f); // bitwise OR
    Show(0xf5 ^ 0x5f); // bitwise XOR
    Show(1 << 5);      // shift 1 left 5 positions

    // don't use these to combine truth-values, use &&, || instead

    return 0;
}
