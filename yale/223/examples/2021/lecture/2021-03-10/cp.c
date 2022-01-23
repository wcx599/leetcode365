#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

int
main(int argc, char **argv)
{

    // copy the contents of first file to second file
    
    FILE *in = fopen(argv[1], "r");
    if(in == 0) {
        perror(argv[1]);
        return 1;
    } 

    FILE *out = fopen(argv[2], "w");
    if(out == 0) {
        perror(argv[2]);
        return 2;
    } 

    int c;
    while((c = getc(in)) != EOF) {
        putc(c, out);
    }

    fclose(in);
    fclose(out);

    return 0;
}
