#include <stdlib.h>

#include <stdio.h>

#include "room.h"

#include "dungeon.h"

#define ABS(x) (x>0?x:-x)

Room* getRandRoom()
{
	Room* room = malloc(sizeof(Room));
	room->w = rand() % (MAX_W - MIN_W + 1) + MIN_W;
	room->h = rand() % (MAX_H - MIN_H + 1) + MIN_H;
	room->x = rand() % (NUM_COL - room->w -1) + 1;
	room->y = rand() % (NUM_ROW - room->h -1) + 1;
	return room;
}

int coexist(Room* room1, Room* room2)
{
	int x1 = room1->x;
	int x2 = room2->x;

	int y1 = room1->y;
	int y2 = room2->y;
	
	int w1 = room1->w;
	int w2 = room2->w;

	int h1 = room1->h;
	int h2 = room2->h;
	
	return x1 + w1 < x2 || x2 + w2 < x1 || y1 + h1 < y2 || y2 + h2 < y1;
}

static void shuffle(int length, int* arr)
{
	while(length>1)
	{
		int num = rand() % length;
		int tmp = arr[num];
		arr[num] = arr[length-1];
		arr[length-1] = tmp;
		length--;
	}
}

void connect(Room* room1, Room* room2, char matrix[NUM_ROW][NUM_COL])
{
	if(!room1)
		printf("room1 is NULL\n");
	if(!room2)
		printf("room2 is NULL\n");
	
	int x1 = room1->w / 2 + room1->x;
	int x2 = room2->w / 2 + room2->x;
	int y1 = room1->h / 2 + room1->y;
	int y2 = room2->h / 2 + room2->y;
	int x = x2 - x1;
	int y = y2 - y1;
	int i;
	const int size = ABS(x) + ABS(y);
	int arr[size];
	for(i=0; i<ABS(x); i++)
		arr[i] = 0;
	for(i=0; i<ABS(y); i++)
		arr[ABS(x)+i] = 1;
	
	shuffle(ABS(x)+ ABS(y), arr);

	if(debug)
	{
		printf("%d steps on x, %d steps on y\n", x, y);
		for(i=0; i<ABS(x)+ABS(y); i++)
			printf("%d", arr[i]);
		printf("\n");
	}

	int curx = x1, cury = y1;

	for(i=0;i<size;i++)
	{
		if(arr[i]) 
		{
			cury += (y>0?1:-1);
		}
		else
		{
			curx += (x>0?1:-1);
		}
		if(matrix[cury][curx]=='#')
			break;
		if(!(matrix[cury][curx]=='.'))
		{	
			matrix[cury][curx]='#';
			h_matrix[cury][curx] = 0;
		}
	}
}

