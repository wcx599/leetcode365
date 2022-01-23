#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

// example of parsing complex input with
// a recursive structure
//
// e.g. ((1+2)*(3+4))
//
// define a context-free grammar
//
// EXPR ::= NUMBER | '(' EXPR OP EXPR ')'
// OP ::= '+' | '*'
// NUMBER ::= DIGIT
// DIGIT ::= '0' .. '9'

static int
peekchar(void)
{
    int c = getchar();
    ungetc(c, stdin);
    return c;
}

// read and compute the value of an expression
static int
readExpr(void)
{
    int c;
    int value;
    int e1;
    int e2;
    int op;
    int closeParen;

    c = peekchar();

    switch(c) {
        case EOF:
            return 0;
        case '(':
            // eat the left parenthesis
            getchar();

            // read parts of expression
            e1 = readExpr();
            op = getchar();
            e2 = readExpr();
            closeParen = getchar();
            // error message would be better
            assert(closeParen == ')');

            switch(op) {
                case '+':
                    return e1 + e2;
                case '*':
                    return e1 * e2;
                case '-':
                    return e1 - e2;
                case '/':
                    return e1 / e2;
                case '%':
                    return e1 % e2;
                default:
                    // error message would be better
                    assert(0);
            }
            
        default:
            // assume number
            if(scanf("%d", &value) == 1) {
                return value;
            } else {
                fprintf(stderr, "bad number!");
                exit(1);
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

    printf("%d\n", readExpr());

    return 0;
}
