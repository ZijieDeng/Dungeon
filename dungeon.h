#ifndef DUNGEON_H
#define DUNGEON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "room.h"

#define ARR_SIZE 10

/* default path for save and load */
char* defaultpath;

unsigned int seed;

int room_count;

uint8_t h_matrix[21][80];

int dungeon_random();

int dungeon_load(char*);

int dungeon_save(char*);

char matrix[NUM_ROW][NUM_COL];

Room* arr[ARR_SIZE];

void placeRoom(Room* room);

void constructMatrix();

void printMatrix();

int coexistAll(Room* room, int number);

#endif

