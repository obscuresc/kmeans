CC = g++
CFLAGS = -Wall -Werror -Wextra -pedantic
DBGCFLAGS = -g -DDEBUG

EXE = main

.PHONY: all debug clean

all: main

debug: main.cpp
	$(CC) $(CFLAGS) $(DBGCFLAGS) -o $@ $^

main: main.cpp
	$(CC) $(CFLAGS) -o $@ $^ 

clean:
	rm -rf main
