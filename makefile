CC = g++
CFLAGS  = -g -Wall -std=c++0x

SRC = ./src/grid.cpp ./include/grid.h ./src/flipIt.cpp ./include/flipIt.h ./src/flipitDisplay.cpp ./include/flipitDisplay.h

all: ./bin/flipIt.o
	$(CC) $(CFLAGS) -o ./flipit.exe ./src/flipitMain.cpp $(SRC)

test: ./bin/flipIt.o ./bin/grid.o
	$(CC) $(CFLAGS) -o ./test.exe ./test/flipit_test.cpp $(SRC)

./bin/flipitDisplay.o: ./src/flipitDisplay.cpp ./include/flipitDisplay.h
	$(CC) $(CFLAGS) -c ./src/flipitDisplay.cpp ./include/flipitDisplay.h -o ./bin/flipitDisplay.o

./bin/flipIt.o: ./src/flipIt.cpp ./include/flipIt.h
	$(CC) $(CFLAGS) -c ./src/flipIt.cpp ./include/flipIt.h -o ./bin/flipitDisplay.o

gridSample: ./bin/grid.o ./bin/gridSample.o
	$(CC) $(CFLAGS) -o ./gridSample.exe ./src/gridSamp.cpp ./src/flipitDisplay.cpp ./include/flipitDisplay.h ./src/grid.cpp ./include/grid.h 
	
./bin/gridSample.o: ./bin/grid.o ./src/gridSamp.cpp
	$(CC) $(CFLAGS) -c ./src/gridSamp.cpp -o ./bin/gridSample.o

./bin/grid.o: ./src/grid.cpp ./include/grid.h
	$(CC) $(CFLAGS) -c ./src/grid.cpp ./include/grid.h -o ./bin/grid.o

clean: 
	rm ./bin/*.o
	