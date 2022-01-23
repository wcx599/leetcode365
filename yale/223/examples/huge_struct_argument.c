#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HUGE (1000000)

struct arrayWrapper {
    int a[HUGE];
};

void
mungeArray(struct arrayWrapper a)
{
    memset(a.a, 1, sizeof(a.a));

    printf("in function: %x\n", a.a[0]);
}

int
main(int argc, char **argv)
{
    struct arrayWrapper a;

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    memset(a.a, 0, sizeof(a.a));

    mungeArray(a);

    printf("in main: %x\n", a.a[0]);

    return 0;
}
