#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>   /* For mmap.  I think mman is short for "memory management." */

#define NUM_COUNTERS (100)      /* number of counters we keep track of */
#define COUNTER_FILE "/tmp/hit" /* where they are stored */
#define NEW_COUNTER_FILE COUNTER_FILE "~"  /* note use of constant string concatenation */

int
main(int argc, char **argv)
{
    int c;
    int *counts;
    int fd;

    if(argc < 2) {
        fprintf(stderr, "Usage: %s number\n", argv[0]);
        exit(1);
    }
    /* else */

    c = atoi(argv[1]);
    if(c < 0 || c >= NUM_COUNTERS) {
        fprintf(stderr, "Counter %d not in range 0..%d\n", c, NUM_COUNTERS - 1);
        exit(2);
    }

    /* open and map the file */
    fd = open(COUNTER_FILE, O_RDWR);
    if(fd < 0) {
        perror(COUNTER_FILE);
        exit(3);
    }
    counts = mmap(0, sizeof(*counts) * NUM_COUNTERS, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

    if(counts == 0) {
        perror(COUNTER_FILE);
        exit(4);
    }

    printf("%d\n", ++counts[c]);

    /* unmap the region and close the file just to be safe */
    munmap(counts, sizeof(*counts) * NUM_COUNTERS);
    close(fd);

    return 0;
}
