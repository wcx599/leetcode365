#include <stdio.h>
#include <assert.h>

int
main(int argc, char **argv)
{
#ifdef SAY_HI
    puts("Hi.");
#else  /* matches #ifdef SAY_HI */
#ifndef BE_POLITE
    puts("Go away!");
#else  /* matches #ifndef BE_POLITE */
    puts("I'm sorry, I don't feel like talking today.");
#endif /* matches #ifndef BE_POLITE */
#endif /* matches #ifdfe SAY_HI */

#ifdef DEBUG_ARITHMETIC
    assert(2+2 == 5);
#endif

    return 0;
}
