#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
    int x;   /* scanf targets */
    int y;

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    printf("scanf says: %d\n", scanf("%d%d", &x, &y));

    return 0;
}
