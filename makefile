CC = g++

main: main.cpp
	$(CC) -o $@ $^ 

clean:
	rm -rf main *.o
