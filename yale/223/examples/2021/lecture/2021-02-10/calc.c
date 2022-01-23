#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <ctype.h> // gets isdigit

int
getNumber(void)
{
    int c;
    int num = 0;
    // keep reading as long as I get a digit
    while((c = getchar()) != EOF && isdigit(c)) {
        num = num * 10 + (c - '0');
    }

    // put back extra character
    ungetc(c, stdin);

    return num;
}


int
main(int argc, char **argv)
{
    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    printf("First number is: %d\n", getNumber());

    // read in numbers one character at a time and print them
    int num = 0;
    int c;
    while((c = getchar()) != EOF) {
        if(isdigit(c)) {
            num = num * 10 + (c - '0');
        } else if (c == '.') {
            // print accumulated number
            printf("[%d]", num);
            num = 0;
        } else {
            putchar(c);
        }
    }

    return 0;
}
