#include <stdio.h>

int
main(int argc, char **argv)
{
    int i;
    int j;
    int x;

    for(i = -3; i < 4; i+=6) {
        for(j = -2; j < 3; j+=4) {
            if(j == 0) continue;
            printf("%d/%d=%d %d%%%d=%d\n", i, j, i/j, i, j, i%j);
        }
    }

    printf("%d/%x = %d\n", 5, 0xffffffff, 5 / 0xffffffff);
    x = 0xffffffff;
    printf("%d / x = %d\n", 5, x, 5/x);

    return 0;
}
