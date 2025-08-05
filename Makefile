CC = cc
CFLAGS = -gdwarf-4 -Wall
IFLAGS = -I/opt/homebrew/Cellar/raylib/5.5/include
LFLAGS = -L/opt/homebrew/Cellar/raylib/5.5/lib

build:
	${CC} ${CFLAGS} ./*.c ${IFLAGS} ${LFLAGS} -lraylib -o ./build/main

run:
	./build/main

clean:
	rm -rf ./build/*
