#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#include "tester.h"
#include "dict.h"

/* avoid retyping casts */
#define Iget(d, key) ((int) dictGet((d), (const void *) (key)))
#define Iset(d, key, value) \
    (dictSet((d), (const void *) (key), (const void *) (value)))

#define STRESS_TEST_ITERATIONS (100000)

int
main(int argc, char **argv)
{
    Dict s2i;
    Dict i2i;
    Dict s2s;
    Dict m2m;
    int i;
    short s;
    int ivalue;

    testerInit();

    TRY { s2i = dictCreate(DictStringOps, DictIntOps); } ENDTRY;
    TRY { i2i = dictCreate(DictIntOps, DictIntOps); } ENDTRY;
    TRY { s2s = dictCreate(DictStringOps, DictStringOps); } ENDTRY;

    /* should be empty initially */
    TEST(Iget(s2i, "foo"), 0);
    TEST(Iget(i2i, 12), 0);
    TEST_ASSERT(dictGet(s2s, "foo") == 0);

    /* initial set */
    TRY { Iset(s2i, "foo", 1); } ENDTRY;
    TRY { Iset(i2i, 12, 2); } ENDTRY;
    TRY { dictSet(s2s, "foo", "bar"); } ENDTRY;
    TEST(Iget(s2i, "foo"), 1);
    TEST(Iget(i2i, 12), 2);
    TEST_ASSERT(!strcmp(dictGet(s2s, "foo"), "bar"));

    /* set again */
    TRY { Iset(s2i, "foo", 3); } ENDTRY;
    TRY { Iset(i2i, 12, 4); } ENDTRY;
    TRY { dictSet(s2s, "foo", "baz"); } ENDTRY;
    TEST(Iget(s2i, "foo"), 3);
    TEST(Iget(i2i, 12), 4);
    TEST_ASSERT(!strcmp(dictGet(s2s, "foo"), "baz"));

    /* now delete */
    TRY { dictSet(s2i, "foo", 0); } ENDTRY;
    TRY { dictSet(i2i, (const void *) 12, 0); } ENDTRY;
    TRY { dictSet(s2s, "foo", 0); } ENDTRY;
    TEST(Iget(s2i, "foo"), 0);
    TEST(Iget(i2i, 12), 0);
    TEST_ASSERT(dictGet(s2s, "foo") == 0);

    /* stress test on i2i */
    TRY {
        for(i = 0; i < STRESS_TEST_ITERATIONS; i++) {
            Iset(i2i, i, i*37);
        }
    } ENDTRY;

    for(i = 0; i < STRESS_TEST_ITERATIONS; i++) {
        TRY { ivalue = Iget(i2i, i); } ENDTRY;
        TEST(ivalue, i*37);
        if(ivalue != i*37) break;
    }

    /* stress test on m2m */
    /* We'll use blocks to hold int keys and short values */
    TRY { 
        m2m = dictCreate(dictMemOps(sizeof(int)),
                          dictMemOps(sizeof(short)));
    } ENDTRY;
    TRY {
        for(i = 0; i < STRESS_TEST_ITERATIONS; i++) {
            s = i % 37;
            dictSet(m2m, &i, &s);
        }
    } ENDTRY;

    for(i = 0; i < STRESS_TEST_ITERATIONS; i++) {
        TRY { ivalue = *((short *) dictGet(m2m, &i)); } ENDTRY;
        TEST(ivalue, i % 37);
        if(ivalue != i % 37) break;
    }

    TRY { dictDestroy(s2i); } ENDTRY;
    TRY { dictDestroy(i2i); } ENDTRY;
    TRY { dictDestroy(s2s); } ENDTRY;
    TRY { dictDestroy(m2m); } ENDTRY;

    testerReport(stdout, argv[0]);
    return testerResult();
}
