#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* takes a bunch of file names on command line */
/* output contents of all the files to stdout */
/* i.e. /bin/cat */

int
main(int argc, char **argv)
{
    int i;  /* loop through argv */
    FILE *f;  /* current open file */
    int c;

    for(i = 1; i < argc; i++) {
        /* fopen opens a file, returns file handle */
        /* "r" = read mode */
        /* "w" = write mode */
        /* "a" = append mode */
        f = fopen(argv[i], "r");
        if(f == 0) {
            /* trouble */
            perror(argv[1]);
            return 1;
        }

        while((c = getc(f)) != EOF) { putchar(c); }

        /* clean up file handle */
        fclose(f);
    }

    return 0;
}
