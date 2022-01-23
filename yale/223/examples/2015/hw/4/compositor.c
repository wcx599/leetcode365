/*
 * Alternate version of ASCII art thing using a queue.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 * Idea of this data structure is that we have a sorted array
 * of pixels, where each pixel specifies a row, column, and character
 * to put in that position.  The sort order is row then column.
 *
 * This is organized as a queue in the sense that we can push
 * new pixels on to the end of it, although as it happens we
 * never actually dequeue anything.
 */
struct pixel {
    int row;
    int col;
    char value;
};

struct queue {
    size_t top;   /* number of elements */
    size_t size;  /* number of allocated slots */
    struct pixel *pixels;  /* pixel values, sorted by row then column */
};

#define QUEUE_INITIAL_SIZE (16)

/* create new empty queue */
struct queue *
queueCreate(void)
{
    struct queue *q;

    q = malloc(sizeof(struct queue));
    assert(q);

    q->top = 0;
    q->size = QUEUE_INITIAL_SIZE;

    q->pixels = malloc(sizeof(struct pixel) * q->size);
    assert(q->pixels);

    return q;
}

/* clean up queue */
void
queueDestroy(struct queue *q)
{
    free(q->pixels);
    free(q);
}

/* add a new pixel to queue */
void
queuePush(struct queue *q, struct pixel p)
{
    while(q->top >= q->size) {
        q->size *= 2;
        q->pixels = realloc(q->pixels, sizeof(struct pixel) * q->size);
        assert(q->pixels);
    }

    q->pixels[q->top++] = p;
}

/* returns malloc'd data, free with queueDestroy */
struct queue *
queueRead(const char *filename)
{
    FILE *f;
    struct queue *q;
    struct pixel p;
    int c;
    
    q = queueCreate();

    f = fopen(filename, "r");
    if(f == 0) {
        perror(filename);
        exit(1);
    }

    p.row = p.col = 0;

    while((c = getc(f)) != EOF) {
        switch(c) {
            case '\n':
                p.row++;
                p.col = 0;
                break;
            case ' ':
                p.col++;
                break;
            default:
                p.value = c;
                queuePush(q, p);
                p.col++;
                break;
        }
    }

    fclose(f);

    return q;
}

/* write pixels in queue to stdout */
void
queueWrite(const struct queue *q)
{
    int outputRow = 0;
    int outputCol = 0;
    int i;

    for(i = 0; i < q->top; i++) {
        while(outputRow < q->pixels[i].row) {
            putchar('\n');
            outputRow++;
            outputCol = 0;
        } 
        while(outputCol < q->pixels[i].col) {
            putchar(' ');
            outputCol++;
        }
        putchar(q->pixels[i].value);
        outputCol++;
    }

    /* end last row */
    putchar('\n');
}

/* 
 * Merge two queues, creating a new, freshly-allocated queue.
 * New queue is sorted.  If there are pixels in both left 
 * and right with the same row and column, the one from right
 * overwrites the one from left.
 */
struct queue *
queueMerge(const struct queue *left, const struct queue *right)
{
    int l = 0;
    int r = 0;
    struct queue *q;

    q = queueCreate();

    while(l < left->top && r < right->top) {
        if(left->pixels[l].row < right->pixels[r].row) {
            queuePush(q, left->pixels[l++]);
        } else if(left->pixels[l].row == right->pixels[r].row) {
            if(left->pixels[l].col < right->pixels[r].col) {
                queuePush(q, left->pixels[l++]);
            } else if(left->pixels[l].col == right->pixels[r].col) {
                /* right wins but both increment */
                queuePush(q, right->pixels[r++]);
                l++;
            } else {
                /* right is earlier */
                queuePush(q, right->pixels[r++]);
            }
        } else {
            /* right is earlier */
            queuePush(q, right->pixels[r++]);
        }
    }

    /* clean out whichever tail is still nonempty */
    while(l < left->top) {
        queuePush(q, left->pixels[l++]);
    }

    while(r < right->top) {
        queuePush(q, right->pixels[r++]);
    }

    return q;
}

/* in-place offset by r rows and c columns */
void
queueOffset(struct queue *q, int r, int c)
{
    int i;

    for(i = 0; i < q->top; i++) {
        q->pixels[i].row += r;
        q->pixels[i].col += c;
    }
}

/* max filename size as promised in assignment text */
#define BUFFER_SIZE (2048)

int
main(int argc, char **argv)
{
    struct queue *merged;   /* holding place for result of merge */
    struct queue *left;     /* accumulated picture */
    struct queue *right;    /* new picture */
    int row;                /* row offset for new picture */
    int col;                /* column offset for new picture */
    char filename[BUFFER_SIZE]; /* filename for new picture */

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    for(left = queueCreate(); scanf("%d %d %s", &row, &col, filename) == 3; left = merged) {
        right = queueRead(filename);
        queueOffset(right, row, col);

        merged = queueMerge(left, right);

        queueDestroy(left);
        queueDestroy(right);
    }

    queueWrite(left);

    queueDestroy(left);

    return 0;
}
