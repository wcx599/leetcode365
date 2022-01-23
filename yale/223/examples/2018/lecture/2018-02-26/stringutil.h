#ifndef _STRINGUTIL_H
#define _STRINGUTIL_H

// some helper routines for the hash table demo
#include <stdio.h>

// Return a malloc'd copy of a string.
// This is probably in the library as strdup,
// but it's not standard, and --pedantic may
// turn it off.
char *strSave(const char *s);

// Fetch the next maximal sequence of alpha chars
// from f, throwing away any preceding non-alpha chars.
// Return value is malloc'd, caller must free.
// Returns null on error or EOF.
char *getWord(FILE *f);

#endif // _STRINGUTIL_H
