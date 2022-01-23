#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct position {
    int x;
    int y;
    const char *comment;
};

typedef struct position Position;

int
sumOfCoords(Position p)
{
    return p.x + p.y;
}


int
main(int argc, char **argv)
{
    Position p;

    p.x = 17;
    p.y = 22;
    p.comment = "hello, world!";

    p.x++;
    
    printf("x=%d y=%d comment=%s\n", p.x, p.y, p.comment);

    printf("%d\n", sumOfCoords(p));


    return 0;
}
