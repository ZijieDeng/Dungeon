#ifndef ROOM_H
#define ROOM_H

#define MIN_W 3
#define MIN_H 2

#define MAX_W 30
#define MAX_H 15

#define NUM_ROW 21
#define NUM_COL 80

#include <stdint.h>

int debug; // 1 if print debug message

typedef struct
{
	uint8_t x, y, w, h;
} Room;

Room* getRandRoom();

int coexist(Room* room1, Room* room2);

static void shuffle(int length, int* arr);

void connect(Room* room1, Room* room2, char[NUM_ROW][NUM_COL]);

#endif
