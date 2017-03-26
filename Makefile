OBJS = main.o room.o dungeon.o helper.o pathFinding.o binheap.o character.o

all: main

clean:
	rm rlg327  *.o

main: $(OBJS)
	gcc -o rlg327 $(OBJS) -g 

%.o: %.c
	gcc -c $< -g
