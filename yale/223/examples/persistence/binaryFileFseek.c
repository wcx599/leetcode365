#include <stdio.h>
#include <stdlib.h>

#define NUM_COUNTERS (100)      /* number of counters we keep track of */
#define COUNTER_FILE "/tmp/hit" /* where they are stored */

int
main(int argc, char **argv)
{
    int c;
    int count;
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

    f = fopen(COUNTER_FILE, "r+b");
    if(f == 0) {
        perror(COUNTER_FILE);
        exit(3);
    }

    /* read counter */
    fseek(f, sizeof(int) * c, SEEK_SET);
    fread(&count, sizeof(int), 1, f);

    printf("%d\n", ++count);

    /* write it back */
    fseek(f, sizeof(int) * c, SEEK_SET);
    fwrite(&count, sizeof(int), 1, f);
    fclose(f);

    return 0;
}
