#include <string.h>
#include <unistd.h>

#include "pathFinding.h"
#include "dungeon.h"
#include "character.h"
#include "binheap.h"

static int32_t compareTurn(const void *key, const void *with)
{
	Character *x = (Character *) key;
	Character *y = (Character *) with;

	/* let PC go first */
	if (x->turn == y->turn)
	{
		if (x->isPC)
			return 1;
		else
			return -1;
	}

	return x->turn - y->turn;
}

int main(int argc, char** argv)
{
	room_count = 0;
	
	pcx = 0, pcy = 0;
	

	char c;
	numMonster = 5;
	int f = 0;

	char* loadPath = NULL;
	char* savePath = NULL;

	char* home = getenv("HOME");
	char* path = "/.rlg327/dungeon";

	defaultpath = malloc(strlen(home) + strlen(path) + 1);
	sprintf(defaultpath, "%s%s", home, path);

	printf("default path: %s\n", defaultpath);

	// check for switches
	int i;
	for(i=0; i<argc; i++)
	{
		if(0==strcmp(argv[i], "--load"))
		{
			if(++i<argc)
				loadPath = argv[i];
			else
				loadPath = defaultpath;
		}
		else if(0==strcmp(argv[i], "--save"))
		{
			if(++i<argc)
				savePath = argv[i];
			else
				savePath = defaultpath;
		}
		// usage: $ ./main --debug
		else if(0==strcmp(argv[i], "--debug"))
		{
			debug = 1;
		}
		else if(0==strcmp(argv[i], "--pc"))
		{
			pcx = atoi(argv[++i]);
			pcy = atoi(argv[++i]);
		}
		else if(0==strcmp(argv[i], "--nummon"))
		{
			if(++i<argc)
				numMonster = atoi(argv[i]);
		}
		else if(0==strcmp(argv[i], "--fight"))
		{
			if(++i<argc)
			{
				f = 1;
				numMonster = 1;
				c = atoi(argv[i]);
				Monster = createCharacter(0);
				Monster->characteristic = c;
			}				
		}
		// usage: $ ./main --seed <value>
		else if(0==strcmp(argv[i], "--seed"))
		{
			if(++i<argc)
				srand(seed = atoi(argv[i]));
		}
		else
		{
			srand(seed = time(NULL));		
		}
	}
	// end of check for switches

	if(loadPath)
	{	
		printf("load path: %s\n", loadPath);
		dungeon_load(loadPath);
	}
	else
	{
		dungeon_random();
	}
	
	if(savePath)
	{
		dungeon_save(savePath);
	}	

	if (!pcx & !pcy)
	{
		PC = createCharacter(1);
		assignRandomLocation(PC);
		pcx = PC->x;//arr[0]->x + arr[0]->w/2;
		pcy = PC->y;//arr[0]->y + arr[0]->h/2;
	}	

	// for free
	int numMonsterOld = 0;
	
	if(f == 1)
	{	
		c_arr[0] = Monster;
		assignRandomLocation(c_arr[0]);
		
		numMonsterOld = 1;
	}
	else 
	{	
		numMonsterOld = numMonster;

		int j;
		for(j = 0; j < numMonster; j++)
		{
			c_arr[j] = createCharacter(0);
			assignRandomLocation(c_arr[j]);
		}

		printMatrix();
		
		Point* pc = makePoint(pcx, pcy);
		
		// printf("init PC at (%d, %d)\n", pc->x, pc->y);

		pathFindingN(pc);
		pathFindingT(pc);
		free(pc);
	}
	
	binheap_t turnheap;
	binheap_init(&turnheap, compareTurn, free);

	binheap_insert(&turnheap, PC);

	for (i=0; i<numMonster; i++)
		binheap_insert(&turnheap, c_arr[i]);
	
	while(!binheap_is_empty(&turnheap))
	{

		while(!binheap_is_empty(&turnheap))
		{
			Character *min = (Character *) binheap_remove_min(&turnheap);
			
			min->turn += 100/min->speed;

			binheap_insert(&turnheap, min);

			if (min->isPC)
				break;
			else
			{
				goMonster(min);
			}
		}

		usleep(100000);
	
		goRandom(PC);
		
		// update Dijkstra's gradient
		Point* p = makePoint(PC->x, PC->y);
		
		// printf("PC at (%d, %d)\n", p->x, p->y);
		
		pathFindingN(p);
		pathFindingT(p);
		free(p);

		/* equal speed version */
		/*
		int i;
		for(i = 0; i < numMonster; i++)
		{
			goMonster(c_arr[i]);
		}
		*/

		printMatrix();
		
		if (numMonster <= 0)
		{
			printf("I win.\n");
			break;
		}

		if (killedPC)
		{
			printf("I am dead.\n");
			break;
		}
	}

	free(PC);

	for(i=0; i<numMonsterOld; i++)
		free(c_arr[i]);
	
	free(defaultpath);

	for(i=0; i<ARR_SIZE; i++)
		free(arr[i]);
}

