/*
 * Translate text into Pig Esperanto, a simplified versoin
 * of Pig Elvish.
 */
#include <stdio.h>
#include <ctype.h>

int
main(int argc, char **argv)
{
    int c;
    int firstLetter;  /* initial letter if any */
    int count = 0;  /* number of letters in the current word so far */

    for(;;) {
        c = getchar();

        if(isalpha(c)) {
            if(count == 0) {
                /* first letter */
                firstLetter = c;
            } else if(count == 1) {
                /* second letter, fix the case */
                if(isupper(firstLetter)) {
                    putchar(toupper(c));
                } else{
                    putchar(tolower(c));
                }
            } else {
                /* just pass it through */
                putchar(c);
            }

            /* always bump count */
            count++;
        } else {
            if(count != 0) {
                /* finish off the previous word */
                if(count > 1) {
                    putchar(tolower(firstLetter));
                } else {
                    putchar(firstLetter);
                }
                
                if(count <= 3) {
                    putchar('a');
                    putchar('n');
                } else {
                    putchar('o');
                }
            }

            /* reset count */
            count = 0;

            if(c == EOF) {
                break;
            } else {
                putchar(c);
            }
        }
    }

    return 0;
}
