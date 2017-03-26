#include "dungeon.h"

#include "helper.h"

#include "character.h"

int dungeon_load(char* filepath)
{
	
	FILE* f = fopen(filepath, "r");
	
	if(!f)
	{
		fprintf(stderr, "Could not open file %s\n", filepath);
		return 1;
	}
		
	char buffer[7];
	fread(buffer, sizeof(*buffer), 6, f);	
	buffer[6] = '\0';
	int vers;
	int size;
	fread(&vers, sizeof(int), 1, f);
	fread(&size, sizeof(int), 1, f);
	unsigned char hardness[1482];
	fread(hardness, sizeof(*hardness), 1482, f);	
	int j;

	size = helper_reverseBytes(size);
	printf("dungeon_load: size is: %d\n", size);
	
	int room_num = (size - 1496)/4;

	constructMatrix();

	int r, c;
	for(r=1; r<20; r++)
	{
		for(c=1; c<79; c++)
		{
			matrix[r][c] = ' ';
		}
	}

	for(r=0;r<19;r++)
	{
		for(c=0;c<78;c++)
		{
			h_matrix[r+1][c+1] = hardness[r*78 + c];
			
			if(!hardness[r*78 + c])
				matrix[r+1][c+1] = '#';
		}
	}
	
	int i;
	for(i=0; i<room_num; i++)
	{
		Room* room = malloc(sizeof(*room));

		uint8_t u8b[4]; // unsigned 8-bit integer buffer
		fread(u8b, sizeof(*u8b), 4, f);
		printf("x=%d, y=%d, w=%d, h=%d\n", 
		u8b[0], u8b[1], u8b[2], u8b[3]);

		room->x = u8b[0];
		room->y = u8b[1];
		room->w = u8b[2];
		room->h = u8b[3];

		arr[i] = room;

		placeRoom(room);		
	}
	//printMatrix();
	
	fclose(f);
	   	
	return 0;
}

int dungeon_save(char* filepath)
{
	FILE* f = fopen(filepath, "w");
	
	if(!f)
	{
		fprintf(stderr, "Could not open file %s\n", filepath);
		return 1;
	}
		
	fwrite("RLG327", sizeof(char), 6, f);	
	
	int vers = 0;
	
	int size = room_count * 4 + 1496;
	printf("dungeon_save: size is: %d\n", size);
	size = helper_reverseBytes(size);
	
	fwrite(&vers, sizeof(int), 1, f);
	fwrite(&size, sizeof(int), 1, f);
	
	unsigned char hardness[1482];
	
	int r, c;
	for(r=0;r<19;r++)
	{
		for(c=0;c<78;c++)
		{
			hardness[r*78 + c] = h_matrix[r+1][c+1];
		}
	}
	
	fwrite(hardness, sizeof(*hardness), 1482, f);	
	
	
	int i;
	for(i=0; i<room_count; i++)
	{
		uint8_t u8b[4]; // unsigned 8-bit integer buffer

		u8b[0] = arr[i]->x;
		u8b[1] = arr[i]->y;
		u8b[2] = arr[i]->w;
		u8b[3] = arr[i]->h;

		fwrite(u8b, sizeof(*u8b), 4, f);
   }

   fclose(f);
   
   return 0;
}

/* function from version 1.01 */
int dungeon_random()
{
	int count = 0;
	int currentArr = 0;
	while(count < 2000 && currentArr < ARR_SIZE)
	{	
		Room* roomCurrent = getRandRoom();
		if(coexistAll(roomCurrent, currentArr))
		{
			arr[currentArr++] = roomCurrent;
		}
		else
		{
			free(roomCurrent);
		}
		count++;
	}
	
	printf("seed: %u\n", seed);
	
	// printf("w: %d, h: %d, x: %d, y:%d\n", r->w, r->h, r->x, r->y);
	constructMatrix();
	
	int i;
	for(i=0; i<currentArr; i++)
	{
		placeRoom(arr[i]);
		
		if(debug)
			printf("w: %d, h: %d, x: %d, y:%d\n",
			arr[i]->w, arr[i]->h, arr[i]->x, arr[i]->y);
		
		connect(arr[i], arr[0], matrix);
	}
	
	//printMatrix();

	return 0;
}

int coexistAll(Room* room, int number)
{
	int i;
	for(i=0; i<number; i++)
	{
		if(!coexist(room, arr[i]))
			return 0;
	}
	return 1;
}

void constructMatrix()
{
	int i;
	int j;
	for(i=0; i<NUM_ROW; i++)
	{
		for(j=0; j<NUM_COL; j++)
		{   
			matrix[i][j] = ' ';
			h_matrix[i][j] = 1 + rand() % 254;
		}
	}
	int r, c;
	for(c=0; c<80; c++)
	{
		matrix[0][c] = ' ';
		matrix[20][c] = ' ';

		h_matrix[0][c]=255;
		h_matrix[20][c]=255;
	}
	for(r=0; r<21; r++)
	{
		matrix[r][0] = ' ';
		matrix[r][79] = ' ';

		h_matrix[r][0]=255;
		h_matrix[r][79]=255;
	}
}

void placeRoom(Room* room)
{
	int i;
	int j;
	for(i=room->x; i< room->x+room->w; i++)
	{
		for(j=room->y; j< room->y+room->h; j++)
		{
			matrix[j][i] = '.';
			h_matrix[j][i] = 0; 
		}
	}
	room_count++;
}

void printMatrix()
{
	int i;
	int j;
	for(i=0; i<	NUM_ROW; i++)
	{	
		for(j=0; j< NUM_COL; j++)
		{
			if(!c_matrix[i][j])
				printf("%c", matrix[i][j]);
			/*else if(c_matrix[i][j]->isPC)
				printf("@");*/
			else  {
				printf("%c", getChar(c_matrix[i][j]));				
				// printf("\nchar: <%c>\n", getChar(c_matrix[i][j]));
			}
		}
		printf("\n");
	}
}
