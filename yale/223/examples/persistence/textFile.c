#include <stdio.h>
#include <stdlib.h>

#define NUM_COUNTERS (100)      /* number of counters we keep track of */
#define COUNTER_FILE "/tmp/hit" /* where they are stored */
#define NEW_COUNTER_FILE COUNTER_FILE "~"  /* note use of constant string concatenation */

int
main(int argc, char **argv)
{
    int c;
    int i;
    int counts[NUM_COUNTERS];
    FILE *f;

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

    f = fopen(COUNTER_FILE, "r");
    if(f == 0) {
        perror(COUNTER_FILE);
        exit(3);
    }

    /* read them in */
    for(i = 0; i < NUM_COUNTERS; i++) {
        fscanf(f, "%d", &counts[i]);
    }
    fclose(f);

    printf("%d\n", ++counts[c]);

    /* write them back */
    f = fopen(NEW_COUNTER_FILE, "w");
    for(i = 0; i < NUM_COUNTERS; i++) {
        fprintf(f, "%d\n", counts[i]);
    }
    fclose(f);

    rename(NEW_COUNTER_FILE, COUNTER_FILE);

    return 0;
}
