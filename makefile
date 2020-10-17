CC = g++
CFLAGS = -Wall -Werror -Wextra -pedantic

.PHONY: clean


main: main.cpp
	$(CC) $(CFLAGS) -o $@ $^ 

clean:
	rm -rf main
