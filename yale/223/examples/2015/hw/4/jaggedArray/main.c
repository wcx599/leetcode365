#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "image.h"

/* disasters will occur if you supply a bigger filename */
#define MAX_FILENAME_LENGTH (2048)

int
main(int argc, char **argv)
{
    Image *img;
    Image *toPaste;
    int row;
    int col;
    char filename[2048];
    FILE *f;

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    img = imageCreate();

    while(scanf("%d %d %s", &row, &col, filename) == 3) {
        f = fopen(filename, "r");
        if(f == 0) {
            perror(filename);
            return 1;
        }

        toPaste = imageCreate();
        imageRead(toPaste, f);

        fclose(f);

        imagePaste(img, row, col, toPaste);
        imageDestroy(toPaste);
    }

    imageWrite(img, stdout);

    imageDestroy(img);

    return 0;
}
