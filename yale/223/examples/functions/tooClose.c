#include "distSquared.h"

#define THRESHOLD (100)

int
tooClose(int x1, int y1, int x2, int y2)
{
    return distSquared(x1 - x2, y1 - y2) < THRESHOLD;
}
