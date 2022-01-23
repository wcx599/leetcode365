#ifndef _ANTS_H
#define _ANTS_H

#include "point.h"
#include "ants.h"

// implements ASCII ants as described in assignment
#define NUMBER_OF_ANTS (256)

typedef struct ants Ants;

// make an anthill
Ants *antsCreate(void);

// and destroy one
void antsDestroy(Ants *);

// set the active ant
void antsSetActive(Ants *, int);

// apply an operator
void antsMove(Ants *, int);

#endif
