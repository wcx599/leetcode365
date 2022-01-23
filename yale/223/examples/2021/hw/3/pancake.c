#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "pancake.h"

// table of instruction lengths
// including arguments
// (used to move to next instruction, or to skip)
static const unsigned int InstructionLength[] = { 3, 3, 2, 3, 1 };

// centralize handling STOP variants
static unsigned int
normalize(unsigned int instruction)
{
    if(instruction > STOP) {
        instruction = STOP;
    } 

    return instruction;
}

// reverse an array
static void
flip(unsigned int *a, unsigned int n)
{
    // special case to avoid n-1 issues
    if(n == 0) { 
        return;
    }

    unsigned int i = 0;
    unsigned int j = n-1;
    unsigned int temp;

    while(i < j) {
        // swap a[i] and a[j]
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;

        // and update indices
        i++;
        j--;
    }
}

// print an array
static void
print(const unsigned int *a, unsigned int n)
{
    // special case for n == 0
    if(n == 0) {
        putchar('\n');
    } else {
        for(unsigned int i = 0; i < n; i++) {
            printf("%u%c", a[i], (i < n-1) ? ' ' : '\n');
        }
    }
}

// execute a program on a given stack of pancakes
void 
runPancakeProgram(unsigned int *memory)
{
    unsigned int pc = 0;  // program counter
    unsigned int next;    // next instruction
    unsigned int instruction; // normalized instruction
    unsigned int x = 0;
    unsigned int y = 0;

    for(;;) {

        instruction = normalize(memory[pc]);

        // compute next pc value
        next = pc + InstructionLength[instruction];

        // collect arguments
        // note this only handles 1, 2, and 3
        switch(InstructionLength[instruction]) {
            case 3:
                y = memory[pc+2];
                // fall through
            case 2:
                x = memory[pc+1];
                // fall through
            case 1:
                break;
            default:
                abort();  // not handled
                break;
        }

#ifdef TRACE_EXECUTION
        fprintf(stderr, "# %u: %u %u %u\n", pc, instruction, x, y);
#endif // TRACE_EXECUTION


        // carry out instruction
        switch(instruction) {

            case FLIP:

                assert(x <= y);
                flip(memory + x, y - x);
                break;

            case PRINT:

                assert(x <= y);
                print(memory + x, y - x);
                break;

            case JUMP:

                next = x;
                break;

            case SKIP:

                if(memory[x] > memory[y]) {
                    // add length of next instruction
                    next += InstructionLength[normalize(memory[next])];
                }
                break;

            case STOP:

                return;

            default:

                abort();  // shouldn't happen
                break;

        }

        pc = next;

    }
}
