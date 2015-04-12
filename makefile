CC 			= g++ -g -Wall -std=c++0x
SRC_GRID    = ./src/grid.cpp ./include/grid.h
SRC_FLIPIT  = ./src/flipIt.cpp ./include/flipIt.h
SRC_DISPLAY = ./src/flipitDisplay.cpp ./include/flipitDisplay.h
SRC_ALL 	= $(SRC_GRID) $(SRC_FLIPIT) $(SRC_DISPLAY)

all: flipitDisplay.o flipIt.o
	$(CC) -o ./bin/flipit ./src/flipitMain.cpp $(SRC_ALL)

start: all
	./bin/flipit

test: flipitDisplay.o flipIt.o grid.o
	$(CC) ./src/flipit.spec.cpp $(SRC_ALL) -o ./bin/test
	./bin/test

flipitDisplay.o: $(SRC_DISPLAY)
	$(CC) -c $(SRC_DISPLAY) -o ./bin/flipitDisplay.o

flipIt.o: $(SRC_FLIPIT)
	$(CC) -c $(SRC_FLIPIT) -o ./bin/flipIt.o

grid.o: $(SRC_GRID)
	$(CC) -c $(SRC_GRID) -o ./bin/grid.o

clean:
	rm ./bin/*.o ./bin/*.exe ./*.exe -f