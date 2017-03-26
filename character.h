#ifndef CHARACTER_H
#define CHARACTER_H

typedef struct
{
	int x;
	int y;
	int isPC;
	char characteristic;
	int speed;
	int dead, turn;
} Character ;

int pcx, pcy;

extern int killedPC;

Character* createCharacter(int);

Character* c_matrix[21][80];

void assignRandomLocation(Character*);

void go(Character*, int, int);

void goRandom(Character*);

Character* PC; 

Character* Monster;

char getChar(Character*);

Character* c_arr[1000];

int numMonster;

void removeMonster(Character*);

void goMonster(Character*);

void goDijkstra(Character*);

void goTelepathy(Character*);

#endif
