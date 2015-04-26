CFLAGS 		= -g -Wall -std=c++0x -I./include/ -I./lib/
CC 			= g++ $(CFLAGS)
SRC_ARRAY    = ./src/array.cpp ./include/array.h
SRC_ALL 	= $(SRC_ARRAY)

test: array.o
	$(CC) ./src/array.spec.cpp $(SRC_ALL) -o ./bin/test
	./bin/test

array.o: $(SRC_ARRAY)
	$(CC) -c $(SRC_ARRAY) -o ./bin/array.o

clean:
	rm ./bin/*.o ./bin/*.exe ./*.exe -f