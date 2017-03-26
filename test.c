#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char** argv)
{
	char *ps = NULL;
	char *pl = NULL;
//	if(argc == 3 && strcmp(argv[1], "--load")==0)
//		p=argv[2];
	int i;
	for(i=1; i<argc; i++)
	{
		if(strcmp(argv[i], "--save")==0)
			if(++i<argc)
				ps = argv[i];
		if(strcmp(argv[i], "--load")==0)
			if(++i<argc)
				pl = argv[i];
	}
	printf("load: %s\n", pl);
	printf("save: %s\n", ps);
	
	FILE* f = fopen(pl, "r");
	
	char buffer[50];
	fread(buffer, sizeof(*buffer), 6, f);
	buffer[6]='\0';
	printf("%s\n", buffer);
	
	int vers;
	int size;
	
	fread(&vers, sizeof(int), 1, f);
	printf("%d\n", vers);
	fread(&size, sizeof(int), 1, f);
	printf("%x\n", size);	

	printf("HOME : %s\n", getenv("HOME"));
}


