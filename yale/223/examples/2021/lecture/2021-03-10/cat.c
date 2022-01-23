#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

int
main(int argc, char **argv)
{

    // copy the contents of all input files
    // specified on command line to stdout
    
    for(int i = 1; i < argc; i++) {
        // process argv[i];
        FILE *f = fopen(argv[i], "r");

        // check to see if it worked
        if(f == 0) {
            // it didn't work
            // use library routine perror to print error message
            perror(argv[i]);
            return 1;
        }

        // it did work
        int c;
        while((c = getc(f)) != EOF) {
            putchar(c);
        }

        fclose(f);
    }

    return 0;
}
