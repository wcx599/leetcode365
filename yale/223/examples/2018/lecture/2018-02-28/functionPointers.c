#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int
putsImportant(const char *s)
{
    return printf("IMPORTANT: %s\n", s);
}

int
main(int argc, char **argv)
{
    // p points to a function that
    // takes a const char *s
    // and return an int
    int (*p)(const char *s);
    int (*a[])(const char *s) = { puts, putsImportant, 0 };
    
    // oddly initialized string
    char s[] = { 'h', 'i', '\0' };

    p = puts;

    (*p)("hello");
    p("world");

    p = putsImportant;

    p("launch missiles");

    for(int i = 0; a[i] != 0; i++) {
        a[i]("hi there");
    }

    // p = 0;
    p("boom");

    return 0;
}
