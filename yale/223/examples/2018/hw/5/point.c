#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "point.h"

// this will need to be updated if POINT_DIMENSION changes
const Point PointZero = { 0, 0, 0 }; 

// compute result of applying operator c to p
Point 
pointMove(Point p, int c) {
    switch(c) {
        // order of coordinates doesn't really matter
        // as long as we are consistent
        case 'h':
            p.coords[0]--;
            break;
        case 'l':
            p.coords[0]++;
            break;
        case 'j':
            p.coords[1]--;
            break;
        case 'k':
            p.coords[1]++;
            break;
        case '<':
            p.coords[2]--;
            break;
        case '>':
            p.coords[2]++;
            break;
        case '*':
            for(int j = 0; j < POINT_DIMENSION; j++) {
                p.coords[j] *= 2;
            }
            break;
        default:
            // do nothing
            ;
    }

    return p;
}
