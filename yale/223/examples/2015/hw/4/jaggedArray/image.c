#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "image.h"

struct row {
    int size;           /* number of columns in this row */
    char *pixels;       /* value of each column */
};

struct image {
    int size;            /* number of rows */
    struct row **rows;   /* pointers to rows */
};

#define INITIAL_ROW_SIZE (16)   /* initial pixels in each row */
#define INITIAL_ROWS (16)       /* initial number of rows */

/* make a new row full of size INITIAL_ROW_SIZE full of TRANSPARENT */
static struct row *
rowCreate(void)
{
    int i;
    struct row *r;

    r = malloc(sizeof(struct row));
    assert(r);

    r->size = INITIAL_ROW_SIZE;

    r->pixels = malloc(r->size);
    assert(r->pixels);

    for(i = 0; i < r->size; i++) {
        r->pixels[i] = TRANSPARENT;
    }

    return r;
}

static void
rowDestroy(struct row *r)
{
    free(r->pixels);
    free(r);
}

static void
rowSet(struct row *r, int col, int value)
{
    int oldSize;
    int i;

    /* make it big enough */
    while(col >= r->size) {
        oldSize = r->size;

        r->size *= 2;

        r->pixels = realloc(r->pixels, r->size);
        assert(r->pixels);

        /* fill in new positions with TRANSPARENT */
        for(i = oldSize; i < r->size; i++) {
            r->pixels[i] = TRANSPARENT;
        }
    }

    r->pixels[col] = value;
}

/* return true if row contains a non-transparent character */
static int
rowNonEmpty(const struct row *r)
{
    int i;

    for(i = 0; i < r->size; i++) {
        if(r->pixels[i] != TRANSPARENT) {
            return 1;
        }
    }

    return 0;
}

Image *
imageCreate(void)
{
    struct image *img;
    int i;

    img = malloc(sizeof(struct image));
    assert(img);

    img->size = INITIAL_ROWS;
    
    img->rows = malloc(sizeof(struct row *) * img->size);
    assert(img->rows);

    for(i = 0; i < img->size; i++) {
        img->rows[i] = rowCreate();
    }

    return img;
}

void
imageDestroy(Image *img)
{
    int i;

    for(i = 0; i < img->size; i++) {
        rowDestroy(img->rows[i]);
    }

    free(img->rows);
    free(img);
}

void
imageSet(Image *img, int row, int col, int value)
{
    int i;
    int oldSize;

    if(value == TRANSPARENT) {
        return;
    }

    /* else */
    while(row >= img->size) {
        oldSize = img->size;

        img->size *= 2;

        img->rows = realloc(img->rows, sizeof(struct row *) * img->size);
        assert(img->rows);

        for(i = oldSize; i < img->size; i++) {
            img->rows[i] = rowCreate();
        }
    }

    rowSet(img->rows[row], col, value);
}

void 
imageRead(Image *img, FILE *f)
{
    int row;
    int col;
    int c;

    row = 0;
    col = 0;

    while((c = getc(f)) != EOF) {
        if(c == '\n') {
            /* new row */
            row++;
            col = 0;
        } else {
            imageSet(img, row, col, c);
            col++;
        }
    }
}

static void
rowWrite(const struct row *r, FILE *f)
{
    int outputSize = 0;
    int i;

    for(i = 0; i < r->size; i++) {
        if(r->pixels[i] != TRANSPARENT) {
            outputSize = i + 1;
        }
    }

    for(i = 0; i < outputSize; i++) {
        putc(r->pixels[i], f);
    }

    putc('\n', f);
}

void
imageWrite(const Image *img, FILE *f)
{
    int outputSize = 0;
    int i;

    for(i = 0; i < img->size; i++) {
        if(rowNonEmpty(img->rows[i])) {
            outputSize = i+1;
        }
    }

    for(i = 0; i < outputSize; i++) {
        rowWrite(img->rows[i], f);
    }
}


void 
imagePaste(Image *dest, int row, int col, Image *src)
{
    int i;
    int j;

    for(i = 0; i < src->size; i++) {
        for(j = 0; j < src->rows[i]->size; j++) {
            imageSet(dest, row + i, col + j, src->rows[i]->pixels[j]);
        }
    }
}
