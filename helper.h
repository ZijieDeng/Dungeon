#ifndef HELPER_H
#define HELPER_H

typedef struct
{
	int x;
	int y;
} Point;

int helper_reverseBytes(int);

Point** getNeighbors(Point*);

int getWeight(Point*);

Point *makePoint(char x, char y);

char changeToLetter(int);
#endif
