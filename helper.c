#include "helper.h"

#include "dungeon.h"

int helper_reverseBytes(int i)
{
	int n1 = i>>24 & 0xff;
	int n2 = i>>8 & 0xff00;
	int n3 = i<<8 & 0xff0000;
	int n4 = i<<24 & 0xff000000;
	return n1 + n2 + n3 + n4;
}

Point* makePoint(char x, char y)
{
	Point *p = malloc(sizeof(Point));
	p->x = x;
	p->y = y;	
	return p;
}

Point** getNeighbors(Point* p)
{
	static Point* neighbors[8];
	int x = p->x;
	int y = p->y;
	neighbors[0] = makePoint(x, y-1);
	neighbors[1] = makePoint(x, y+1);
	neighbors[2] = makePoint(x-1, y);
	neighbors[3] = makePoint(x+1, y);
	neighbors[4] = makePoint(x-1, y-1);
	neighbors[5] = makePoint(x+1, y-1);
	neighbors[6] = makePoint(x+1, y+1);
	neighbors[7] = makePoint(x-1, y+1);

	return neighbors;
}

int getWeight(Point *p)
{
	int px = p->x;
	int py = p->y;
	
	return h_matrix[py][px] / 60 + 1;
	
	/*
	if(h_matrix[py][px]<85)
		return 1;
	else if(h_matrix[py][px]>85 && h_matrix[py][px]<171)
		return 2;
	else if(h_matrix[py][px]>171 && h_matrix[py][px]<255)
		return 3;
	return -1;
	*/
}

char changeToLetter(int dis)
{
	if(dis < 10)
		return dis + '0';
	else if(dis >= 10 && dis < 36)
		return dis - 10 + 'a' ;
	else if(dis >= 36 && dis < 62)
		return dis - 36 + 'A';
	else
		return -1;
}

