#ifndef _TST_H
#define _TST_H

typedef struct tst Tst;

#define EMPTY_TST (0)

void tstInsert(Tst **root, const char *);

int tstContains(const Tst *root, const char *);

void tstDestroy(Tst *root);

void tstPrint(const Tst *root);

#endif
