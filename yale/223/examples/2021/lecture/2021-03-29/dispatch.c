#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

// dispatch table demo

static int
hello(int argc, char **argv)
{
    puts("hi there");

    return 0;
}

static int
goodbye(int argc, char **argv)
{
    puts("goodbye!");

    return 0;
}

static int
echo(int argc, char **argv)
{
    for(int i = 1; i < argc; i++) {
        puts(argv[i]);
    }

    return 0;
}

static int
fail(int argc, char **argv)
{
    puts("you lose");
    return 2;
}

// one row of the dispatch table
struct dispatchRow {
    const char *command;
    int (*handler)(int argc, char **argv);
};

int
main(int argc, char **argv)
{

    // for more commands, we might want to use
    // a hash table
    struct dispatchRow dispatchTable[] = {
        { "hello", hello },
        { "goodbye", goodbye },
        { "echo", echo },
        { "fail", fail },
        { 0, 0 }
    };

    if(argc < 2) {
        goto fail;
    }

    // find argv[1] in table and run
    // corresponding handler
    for(int i = 0; dispatchTable[i].command; i++) {
        if(!strcmp(dispatchTable[i].command, argv[1])) {
            // match
            return dispatchTable[i].handler(argc - 1, argv + 1);
        }
    } 

    // no match
fail:
    fprintf(stderr, "Usage: %s command [args]\n", argv[0]);
    fprintf(stderr, "Commands:");
    for(int i = 0; dispatchTable[i].command; i++) {
        fprintf(stderr, " %s", dispatchTable[i].command);
    }
    putc('\n', stderr);

    return 1;
}
