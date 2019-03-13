#Adapted from the tutorial "How to Create a Simple Makefile - Introduction to Makefiles"
#https://www.youtube.com/watch?v=_r7i5X0rXJk
#and "A Simple Makefile Tutorial"
#http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

CC = g++
CFLAGS = -g -std=c++11 -MD -MP
OBJ = main.o Menu.o Game.o Space.o LockedRoom.o ItemRoom.o MonsterRoom.o Character.o Monster.o Item.o
PROJECT = FinalProject_Jones_Robert
BIN = text-game

$(BIN): $(OBJ)
	$(CC) -o $@ $(CFLAGS) $(OBJ)

main.o: main.cpp
	$(CC) -c $(CFLAGS) $^

Menu.o: Menu.cpp
	$(CC) -c $(CFLAGS) $^

Game.o: Game.cpp
	$(CC) -c $(CFLAGS) $^

Space.o: Space.cpp
	$(CC) -c $(CFLAGS) $^

LockedRoom.o: LockedRoom.cpp
	$(CC) -c $(CFLAGS) $^

MonsterRoom.o: MonsterRoom.cpp
	$(CC) -c $(CFLAGS) $^

ItemRoom.o: ItemRoom.cpp
	$(CC) -c $(CFLAGS) $^

Character.o: Character.cpp
	$(CC) -c $(CFLAGS) $^

Monster.o: Monster.cpp
	$(CC) -c $(CFLAGS) $^

Item.o: Item.cpp
	$(CC) -c $(CFLAGS) $^

valgrind:
	@valgrind --leak-check=full --track-origins=yes ./$(BIN)

zip:
	zip -D $(PROJECT).zip *.cpp *.hpp *.pdf *.txt makefile

clean:
	rm -f core $(OBJ) *.d *~ $(BIN)
