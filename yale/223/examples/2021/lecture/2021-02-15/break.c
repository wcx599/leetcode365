#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    int c;

    // print input chars until newline or EOF
    while((c = getchar()) != EOF && c != '\n') {
        printf("(%c)\n", c);
    }

    // same thing using break
    // for(;;) is an infinite loop (no test == true)
    // some people pronounce this "for ever"
    for(;;) {
        c = getchar();

        // using break lets us reverse the test
        if(c == EOF || c == '\n') {
            // escape from innermost containing loop or switch
            break;
        }

        printf("[%c]\n", c);
    }

    // with nested statements, might have to use goto instead
    for(;;) {
        c = getchar();

        switch(c) {
            case EOF:
            case '\n':
                // break here will just exit the switch
                goto escapeForLoop;

            default:
                // default default case, do nothing
                break;
        }

        printf("{%c}\n", c);
    }

escapeForLoop:
        // label must go before a statement
        // so we use a dummy statement
        ; 

    return 0;
}
