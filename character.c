#include <stdlib.h>

#include "character.h"

#include "room.h"

#include "dungeon.h"

#include "helper.h"

#include "pathFinding.h"

int killedPC = 0;

void goMonster(Character* character)
{
	//printf("monster before go: %c\n", getChar(character));
	
	if (character->characteristic & 8 && rand()%2)
		goRandom(character);
	else if (character->characteristic & 1)
		goDijkstra(character);
	else if (character->characteristic & 2)
		goTelepathy(character);
	else
		goRandom(character);

	//printf("monster after go: (%d, %d)\n\n", character->x, character->y);
	
}

void goTelepathy(Character* character)
{
	int newX, newY;
	if(character->x > PC->x)
		newX = character->x - 1;
	if(character->x < PC->x)
		newX = character->x + 1;
	if(character->x == PC->x)
		newX = character->x;
	if(character->y > PC->y)
		newY = character->y - 1;
	if(character->y < PC->y)
		newY = character->y + 1;
	if(character->y == PC->y)
		newY = character->y;	
	go(character, newX, newY);
}

void goDijkstra(Character* character)
{
	//printf("%c :", getChar(character));
	Point* p = makePoint(character->x, character->y);
	Point** arr = getNeighbors(p);
	Point* min = p;
	if(character->characteristic & 4)
	{
		int i;
		for(i = 0; i<8 ; i++)
		{
			Point* n = arr[i];
			if(distanceT[n->y][n->x]<distanceT[min->y][min->x])
				min = n;
		}
	}
	else 
	{
		// printf("Dijkstra non-tunneling");

		int i;
		for(i = 0; i<8 ; i++)
		{
			Point* n = arr[i];
			if(distanceN[n->y][n->x]<distanceN[min->y][min->x])
				min = n;
		}
	}

	// printf("character at (%d, %d)\n", character->x, character->y);
	// printf("min at (%d, %d)\n\n", min->x, min->y);

	go(character, min->x, min->y);

	free(p);

	int i;	
	for(i=0; i<8; i++)
		free(arr[i]);
}

Character* createCharacter(int isPC)
{
	Character* character = malloc(sizeof(Character));
	character->isPC = isPC;
	character->characteristic = rand() % 16 ;
	
	character->dead = 0;
	character->turn = 0;
	
	if (isPC)
		character->speed = 10;
	else
		character->speed = rand()%16 + 5;
		
	return character;
}

void assignRandomLocation(Character* character)
{
	int num = rand() % 	ARR_SIZE;
	Room* room = arr[num];
	character->x = rand() % (room->w) + room->x;
	character->y = rand() % (room->h) + room->y;
	c_matrix[character->y][character->x] = character;
}

void go(Character* character, int x, int y)
{
	if (character->x == x && character->y == y)
		return;
	
	Character *killed = c_matrix[y][x];

	if(c_matrix[y][x] && !(killed->isPC))
	{
		// printf("remove %c\n", getChar(killed));
		removeMonster(c_matrix[y][x]);
	}

	c_matrix[character->y][character->x] = NULL;
	c_matrix[y][x] = character;

	if (h_matrix[y][x] > 0 && h_matrix[y][x] < 255)
	{
		h_matrix[y][x] = 0;
		matrix[y][x] = '#';
	}

	character->x = x;
	character->y = y;

	if (killed && killed->isPC)
		killedPC = 1;
}

void goRandom(Character* character)
{
	//	printf("%c", getChar(character));
	int num;
	char ch = character->characteristic;
	Point* point = makePoint(character->x, character->y), *dst;
	Point** p_arr = getNeighbors(point);	
	while(1)
	{
		num = rand() % 8;
		Point *p = p_arr[num];
		if(!character->isPC && (ch & 4)
			&& h_matrix[p->y][p->x]<255)
		{
			dst = p;
			break;
		}
		else if(!h_matrix[p->y][p->x])
		{
			dst = p;
			break;
		}
	}
	 
	go(character, dst->x, dst->y);
	free(point);
	
	int i;
	for(i=0; i<8; i++)
	{
		free(p_arr[i]);
	}
}

char getChar(Character* character)
{
	if(character->isPC)
		return '@';
	char c = character->characteristic;
	if(c >= 0 && c <= 9)
		return c + '0';
	else if(c >= 10 && c <= 15)
		return c - 10 + 'a';
	return -1;
}

void removeMonster(Character* character)
{
	int i;

	for(i = 0; i < numMonster; i++)
	{
		if(character == c_arr[i])
		{
			c_arr[i] = c_arr[numMonster-1];
			c_arr[numMonster-1] = character;
			numMonster--;
			break;		
		}				
	}					
}						
