#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// go down n floors, then come back up
void
elevator(int n)
{
    printf("going down: %d\n", n);
    
    if(n <= 0) {
        puts("at the bottom");
    } else {
        elevator(n-1);
    }

    printf("going up: %d\n", n);
}

int
main(int argc, char **argv)
{

    if(argc != 2) {
        fprintf(stderr, "Usage: n %s\n", argv[0]);
        return 1;
    }

    elevator(atoi(argv[1]));

    return 0;
}
