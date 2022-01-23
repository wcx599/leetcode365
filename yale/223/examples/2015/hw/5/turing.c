/*
 * Simple Turing machine simulator.
 *
 * Tape holds symbols 0 (default) through 2.
 *
 * Controller programming is specified in argv:
 *
 * argv[i] gives transitions for state i as six characters.
 *
 * Each triple of characters is <action><direction><new-state>
 *
 * where <action> is one of:
 *
 *  a,b,c: write this value to tape
 *
 * <direction> is one of:
 *
 *  -: go left
 *  +: go right
 *  .: stay put
 *
 * The three pairs give the transition for reading 0, 1, 2 from tape.
 *
 * State 0 is the halting state.
 *
 * On halting, prints number of transitions followed by contents
 * of all tape cells that have ever been visited by the 
 * finite-state controller.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>

struct configuration {
    unsigned int state;/* state of head */
    size_t leftmost;   /* leftmost cell visited */
    size_t rightmost;  /* rightmost cell visited */
    size_t current;    /* current cell */
    size_t tapeLength; /* current allocated space for tape */
    char *tape;        /* contents of cells */
};

/* increase the size of the tape and recenter contents in middle */
void
configurationExpand(struct configuration *c)
{
    size_t newTapeLength;
    char *oldTape;
    char *newTape;
    size_t i;
    ssize_t offset;

    newTapeLength = 4*c->tapeLength;
    newTape = malloc(newTapeLength);
    assert(newTape);

    for(i = 0; i < newTapeLength; i++) {
        newTape[i] = 0;
    }

    /* copy old tape */
    offset = newTapeLength / 2 - c->current;

    for(i = c->leftmost; i <= c->rightmost; i++) {
        newTape[i + offset] = c->tape[i];
    }

    oldTape = c->tape;
    c->tape = newTape;
    c->tapeLength = newTapeLength;
    c->current += offset;
    c->leftmost += offset;
    c->rightmost += offset;

    free(oldTape);
}

#define INITIAL_TAPE_LENGTH (16)

struct configuration *
configurationCreate(void)
{
    struct configuration *c;
    size_t i;

    c = malloc(sizeof(struct configuration));
    assert(c);

    c->state = 1;
    c->tapeLength = INITIAL_TAPE_LENGTH;
    c->leftmost = c->rightmost = c->current = c->tapeLength / 2;
    c->tape = malloc(c->tapeLength);
    assert(c->tape);

    for(i = 0; i < c->tapeLength; i++) {
        c->tape[i] = 0;
    }

    return c;
}

void
configurationDestroy(struct configuration *c)
{
    free(c->tape);
    free(c);
}

#define SYMBOL_BASE ('a')
#define STATE_BASE ('0')

/* used for debugging mostly */
void
configurationPrint(const struct configuration *c)
{
    size_t i;

    for(i = c->leftmost; i < c->current; i++) {
        putchar(' ');
    }
    putchar(STATE_BASE + c->state);
    putchar('\n');

    for(i = c->leftmost; i <= c->rightmost; i++) {
        putchar(SYMBOL_BASE + c->tape[i]);
    }
    putchar('\n');
}

int
main(int argc, char **argv)
{
    struct configuration *c;
    char cellValue;
    const char *transition;
    size_t steps;

    if(argc == 1) {
        fprintf(stderr, "Usage: %s transitions\n", argv[0]);
        return 1;
    }

    c = configurationCreate();
    steps = 0;

    while(c->state != 0) {
        steps++;

        /* execute the next transition */
        assert(c->state < argc);

        cellValue = c->tape[c->current];
        assert(0 <= cellValue);
        assert(3*(cellValue+1) <= strlen(argv[c->state]));

        transition = argv[c->state] + 3*c->tape[c->current];

        c->tape[c->current] = transition[0] - SYMBOL_BASE;

        switch(transition[1]) {
            case '-':
                if(c->current == 0) {
                    configurationExpand(c);
                }
                c->current--;
                if(c->current < c->leftmost) {
                    c->leftmost = c->current;
                }
                break;
            case '+':
                if(c->current == c->tapeLength - 1) {
                    configurationExpand(c);
                }
                c->current++;
                if(c->current > c->rightmost) {
                    c->rightmost = c->current;
                }
                break;
            case '.':
                /* do nothing */
                break;
            default:
                fprintf(stderr, "Bad direction '%c'\n", transition[2]);
                exit(2);
                break;
        }

        c->state = transition[2] - STATE_BASE;

#ifdef PRINT_CONFIGURATION
        configurationPrint(c);
#endif
    }

    /* print number of steps */
    printf("%zu\n", steps);

    configurationDestroy(c);

    return 0;
}
