OBJS = main.o funcs.o globals.o texture.o text.o pacman.o map.o ghost_manager.o ghost.o blinky.o clyde.o pinky.o inky.o
CC = g++
COMPILER_FLAGS = -w -c -std=c++11
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

OBJ_NAME = pacman

Pacman: $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)

main.o: main.cpp funcs.h globals.h pacman.h constants.h map.h ghost_manager.h
	$(CC) $(COMPILER_FLAGS) main.cpp

map.o: map.h map.cpp constants.h texture.h
	$(CC) $(COMPILER_FLAGS) map.cpp

ghost_manager.o: ghost_manager.h ghost_manager.cpp ghost.h blinky.h clyde.h pinky.h inky.h texture.h 
	$(CC) $(COMPILER_FLAGS) ghost_manager.cpp

ghost.o: ghost.h ghost.cpp map.h texture.h constants.h
	$(CC) $(COMPILER_FLAGS) ghost.cpp

blinky.o: blinky.h blinky.cpp ghost.h constants.h map.h
	$(CC) $(COMPILER_FLAGS) blinky.cpp

clyde.o: clyde.h clyde.cpp ghost.h constants.h map.h
	$(CC) $(COMPILER_FLAGS) clyde.cpp

pinky.o: pinky.h pinky.cpp ghost.h constants.h map.h
	$(CC) $(COMPILER_FLAGS) pinky.cpp

inky.o: inky.h inky.cpp ghost.h constants.h map.h
	$(CC) $(COMPILER_FLAGS) inky.cpp

pacman.o: pacman.h pacman.cpp texture.h constants.h map.h
	$(CC) $(COMPILER_FLAGS) pacman.cpp

funcs.o: funcs.h funcs.cpp globals.h constants.h
	$(CC) $(COMPILER_FLAGS) funcs.cpp

globals.o: globals.h globals.cpp texture.h
	$(CC) $(COMPILER_FLAGS) globals.cpp

texture.o: texture.h texture.cpp globals.h
	$(CC) $(COMPILER_FLAGS) texture.cpp

text.o: text.h text.cpp texture.h constants.h
	$(CC) $(COMPILER_FLAGS) text.cpp

clean:
	rm *.o pacman