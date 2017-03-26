First name: Zijie
Last name: Deng
ID: 883871989

This project is about adding player character and Monsters to the dungeon, and make them move around to "kill each other".
 
Specification:
	1. Randomly assign locations for PC and Monsters, which will always be placed in room.
	2. PC is represented by '@', Monsters are represented by char from '0' to '9' and 'a' to 'f'.
	3. goMonsters determines whether monsters have Intelligence, Telepathy, Tunneling Ability, and Erratic behavior or not, and call goDijkstra, goTelepathy, and goRandom respectively.
	4. correctly remove character, when new arrival kills the original occupant.
	5. correctly find path for tunnelers, non-tunnelers, tunnler can move through rocks, others cannot.
	6. end game once PC is killed.

Methods about Character:
	Create point:
		1. typedef struct{}Character;
		2. Character* createCharacter(int);
	Assign Random Locations for characters:
		void assignRandomLocation(Character*);
	Remove character, if new arrival kills the original occupant:
		void removeMonster(Character*);

Methods about Moving in dungeon:	
	The method for all, which takes Character*, determine the abilities:
		void goMonster(Character*);
	The method for going from original point to another point:
		void go(Character*);
	The method for moving randomly, including determine tunneler: 
		void goRandom(Character*);
	The method for intelligent monsters to move:
		void goDijkstra(Character*);
	The method for Telepathy monsters to move:
		void goTelepathy(Character*);

main.c contains:
	(1)In a for loop to check for swiches:
		--nommon
		Example: if user enter  "--nommon NUMBER" after "./rlg327":
			change numMonster to that NUMBER.
	(2)In a while loop to move characters and PC, which also calls pathFinding to update current PC location.

Makefile:
	This makefile helps to compile main.c room.c room.h dungeon.c dungeon.h
	pathFinding.c pathFinding.h character.c character.h
	Example:
		Enter "make" to complie.
		Enter "make clean" to remove "./main" and all file ended with ".o"
		Enter "./rlg327" to run the preject.
