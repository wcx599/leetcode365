#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

// demonstrating various string-processing idioms

// print expression and its formatted value
// parameter format is a printf format specifier
// parameter x is the expression to evaluate
// (non-syntactic macro for pedagogical use only)
#define Show(format, x) (printf("%30s == %" #format "\n", #x, (x)))

// like puts but I wrote it
void
myPuts(const char *s)
{
    while(*s != '\0') {
        putchar(*s++);
    }
    putchar('\n');
}

// rewrite of strlen
size_t
myStrlen(const char *s)
{
    size_t i;

    for(i = 0; *s != '\0'; i++, s++);

    return i;
}

// strcpy
char *
myStrcpy(char *dest, const char *src)
{
    char *d = dest;

    while((*d++ = *src++));

    return dest;
}

char *
myStrcat(char *dest, const char *src)
{
    myStrcpy(dest + myStrlen(dest), src);

    return dest;
}

int
myStrcmp(const char *x, const char *y)
{
    // walk across x and y
    // until *x != *y or both are '\0'
    while((*x == *y) && *x != '\0') {
        x++;
        y++;
    }

    return *x - *y;
}

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    const char *fixedString = "this is a constant string";

    Show(s, fixedString);
    Show(s, fixedString + 5);
    Show(s, fixedString + 15);
    Show(s, fixedString + 125);  // might segfault, might not

    myPuts(fixedString);

    // some built-in string functions declared in string.h
    
    // strlen returns number of non-null characters in its argument
    Show(zu, strlen("cat"));

    // strcpy is like assignment for strings, copies
    // second argument to first
    
    char buf[20]; // 20 is picked to be long enough we hope

    // strcpy(dest, src)
    // copies src to dest, returns dest
    Show(s, strcpy(buf, "cat"));
    Show(s, buf);

    // since buf is not const, can modify it
    Show(s, strcpy(buf+3, "dog"));
    Show(s, buf);

    // strcat tacks extra chars onto the end of a string
    Show(s, strcat(buf, "bus"));
    Show(s, buf);

    // can initialize to a constant
    char a[100] = "abc";
    Show(s, a);

    // can even omit size
    char a2[] = "abc";
    Show(s, a2);

    // next trick: reimplement str* routines myself
    Show(s, buf);
    Show(zu, myStrlen(buf));

    Show(s, myStrcpy(buf, "abcdef"));
    Show(s, buf);

    Show(s, myStrcat(buf, "ghi"));

    // testing string equality using strcmp
    // strcmp(x, y) returns
    // <0 if x < y in lexicographic order
    //  0    x equals y
    // >0 if x > y in lexicographic order
    Show(d, strcmp("abc", "abd"));
    Show(d, strcmp("abc", "abc"));
    Show(d, strcmp("abx", "abc"));
    Show(d, strcmp("ab", "abc"));

    Show(d, myStrcmp("abc", "abqxr"));

    char combination[] = "aaa";

    while(strcmp(combination, "aaq") != 0) {
        printf("%s failed\n", combination);
        combination[2]++;
    }

    Show(p, "abc");
    Show(p, "def");
    Show(p, "aba");
    Show(d, "abc" < "def");
    Show(d, "abc" > "aba");

    // difference between x++, *x++, and (*x)++
    char test[] = "abcdefghij";
    Show(s, test);

    char *x = test;

    Show(p, x);
    Show(s, x);

    // x++ adds to the address stored in x
    Show(p, x++);
    Show(p, x);
    Show(s, x);

    // *x++ incs x, returns value pointed to by old x
    Show(c, *x++);
    Show(p, x);
    Show(s, x);

    // (*x)++ incs value pointed to by x, returns old value
    Show(c, (*x)++);
    Show(p, x);
    Show(s, x);
    Show(s, test);

    // split *x++ as x++, then *
    char *x1;

    Show(p, x1 = x++);
    Show(p, x1);
    Show(s, x1);
    Show(p, x);
    Show(s, x);
    Show(c, *x1 = '7');
    Show(s, test);

    // too many ++s
    Show(p, x);
    Show(s, x);
    Show(s, test);
    Show(c, (*x++)++);
    Show(p, x);
    Show(s, x);
    Show(s, test);

    // sprintf does printf to string
    Show(d, sprintf(test, "[%d == %d]", 2, 3));
    Show(s, test);

    char dest[] = "0123";      // allocate array of 5 chars, dest points to first
    const char *d2 = "0123";   // d2 points to first character in constant
    printf("%p\n", dest);
    printf("%s\n", dest);
    printf("%p\n", d2);
    printf("%s\n", d2);

    *dest = 'Z';
    puts(dest);

    // *d2 = 'Q';  // compile time error
    puts(d2);

    // myStrcpy(d2, "def");   // segfault at run time
    
    const char *d3 = "abc";
    Show(p, d3);
    Show(s, d3);
    Show(p, d3 = "def");
    Show(s, d3);

    return 0;
}
