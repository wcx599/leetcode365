#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int
main(int argc, char **argv)
{

    if(argc != 3) {
        fprintf(stderr, "Usage: %s source destination\n", argv[0]);
        return 1;
    }

    FILE *src = fopen(argv[1], "r");

    if(src == 0) {
        perror(argv[1]);
        exit(2);
    }

    FILE *dest = fopen(argv[2], "w");

    if(dest == 0) {
        perror(argv[2]);
        exit(3);
    }

    int c;

    while((c = getc(src)) != EOF) {
        putc(c, dest);
    }

    fclose(src);
    fclose(dest);

    return 0;
}
