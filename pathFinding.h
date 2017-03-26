#include <stdio.h>

#include "binheap.h"

#include "helper.h"

#define INF (10000)

int distanceT[21][80];
int distanceN[21][80];

void pathFindingN(Point*);
void pathFindingT(Point*);

