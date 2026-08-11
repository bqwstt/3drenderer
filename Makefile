CC = gcc
CFLAGS = -Wall -std=c99 -g -O0 -Isrc
SDLFLAGS = -lSDL3 -Wl,-rpath,@executable_path/lib
EXE = 3d

SRC = main.c $(wildcard src/*.c)

.PHONY: build run clean

build:
	$(CC) $(SRC) $(CFLAGS) -L./lib $(SDLFLAGS) -o $(EXE)

run: build
	./$(EXE)

clean:
	rm -f $(EXE)
	rm -rf $(EXE).dSYM
