#include <stdio.h>

#include "dungeon.h"

#include "pathFinding.h"

#include "binheap.h"

#include "helper.h"

#define INF (10000)

int32_t compareN(const void *key, const void *with)
{
	Point *p1 = (Point *) key;
	Point *p2 = (Point *) with;
 	int p1x = p1->x;
	int p1y = p1->y;
	int p2x = p2->x;
	int p2y = p2->y;
	return distanceN[p1y][p1x] - distanceN[p2y][p2x];
}

int32_t compareT(const void *key, const void *with)
{
	Point *p1 = (Point *) key;
	Point *p2 = (Point *) with;
	int p1x = p1->x;
	int p1y = p1->y;
	int p2x = p2->x;
	int p2y = p2->y;
	return distanceT[p1y][p1x] - distanceT[p2y][p2x];	
}

void pathFindingN(Point* p)
{
	binheap_node_t *nodemap[21][80];
	
	int px = p->x;
	int py = p->y;
	
	binheap_t h;
	binheap_init(&h, compareN, free);
	
	int r, c;
	for(r=1; r<20; r++)
	{
		for(c=1; c<79; c++)
		{	
			distanceN[r][c] = INF;
			Point *point = makePoint(c, r);

			nodemap[r][c] = binheap_insert(&h, point);
		}
	}
	
	for(c=0; c<80; c++)
	{
		distanceN[0][c] = INF;
		distanceN[20][c] = INF;
	}
	for(r=0; r<21; r++)
	{
		distanceN[r][0] = INF;
		distanceN[r][79] = INF;
	}
		
	distanceN[py][px] = 0;
	binheap_decrease_key(&h, nodemap[py][px]);

	while(!binheap_is_empty(&h))
	{
		Point *min =(Point *) binheap_remove_min(&h);

		nodemap[min->y][min->x] = NULL;

		Point** arr = getNeighbors(min);
		int weight = 1;
		int distance = distanceN[min->y][min->x] + weight;
		
		// free(min);
		
		int i;
		for(i=0; i<8; i++)
		{			
			Point* neighbor = arr[i];
			int pnx = neighbor->x;
			int pny = neighbor->y;
			free(neighbor);
			
			if(pnx>0 && pnx<79 && pny>0 && pny<20)
			{
				if (!h_matrix[pny][pnx] && distanceN[pny][pnx] > distance)
				{
					distanceN[pny][pnx] = distance;
					
					if (nodemap[pny][pnx])
						binheap_decrease_key(&h, nodemap[pny][pnx]);
				}
			}
		}
	}

	binheap_delete(&h);

/*	
	for(r=0; r<21; r++)
	{
		for(c=0; c<80; c++)
		{
			if (h_matrix[r][c])
				printf(" ");
			else
			{
				char ch = changeToLetter(distanceN[r][c]);
				if (ch<0)
					printf("%c", matrix[r][c]);
				else
					printf("%c", ch);
			}
		}
		printf("\n");
	}
*/
}

void pathFindingT(Point* p)
{
	binheap_node_t *nodemap[21][80];
	
	int px = p->x;
	int py = p->y;
	
	binheap_t h;
	binheap_init(&h, compareT, free);
	
	int r, c;
	for(r=1; r<20; r++)
	{
		for(c=1; c<79; c++)
		{	
			distanceT[r][c] = INF;
			Point *point = makePoint(c, r);

			nodemap[r][c] = binheap_insert(&h, point);
		}
	}

	for(c=0; c<80; c++)
	{
		distanceT[0][c] = INF;
		distanceT[20][c] = INF;
	}
	for(r=0; r<21; r++)
	{
		distanceT[r][0] = INF;
		distanceT[r][79] = INF;
	}
	
	distanceT[py][px] = 0;
	binheap_decrease_key(&h, nodemap[py][px]);
	
	while(!binheap_is_empty(&h))
	{
		Point *min =(Point *) binheap_remove_min(&h);

		nodemap[min->y][min->x] = NULL;
		
		Point** arr = getNeighbors(min);
		
		int weight = getWeight(min);
		int distance = distanceT[min->y][min->x] + weight;

		// free(min);
		
		int i;
		for(i=0; i<8; i++)
		{			
			Point* neighbor = arr[i];
			int pnx = neighbor->x;
			int pny = neighbor->y;
			
			free(neighbor);
			
			if(pnx>0 && pnx<79 && pny>0 && pny<20)
			{
				// printf("(%d, %d)\n", pnx, pny);
				if (distanceT[pny][pnx] > distance)
				{
					distanceT[pny][pnx] = distance;
					
					if (nodemap[pny][pnx])
						binheap_decrease_key(&h, nodemap[pny][pnx]);
				}
			}
		}
	}

	binheap_delete(&h);

	/*for(r=0; r<21; r++)
	{
		for(c=0; c<80; c++)
		{
			if (h_matrix[r][c]==255)
				printf(" ");
			else
			{
				char ch = changeToLetter(distanceT[r][c]);
				if (ch<0)
					printf("%c", matrix[r][c]);
				else
					printf("%c", ch);
			}
		}
		printf("\n");
	}*/
}
