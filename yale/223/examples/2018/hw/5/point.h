#ifndef _POINT_H
#define _POINT_H

#define POINT_DIMENSION (3)

typedef struct point {
    int coords[POINT_DIMENSION];  // coordinates
} Point;

#define POINT_OPERATORS "hjkl<>*"

#define POINT_OPERATORS_NUMBER (sizeof(POINT_OPERATORS) - 1)  // don't count the null

// compute result of applying operator c to p
Point pointMove(Point p, int c);

// the origin
extern const Point PointZero;

#endif
