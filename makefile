CC = g++
CFLAGS  = -g -Wall

SRC = ./src/grid.cpp ./include/grid.h ./src/flipitEngine.cpp ./include/flipitEngine.h ./src/flipitDisplay.cpp ./include/flipitDisplay.h

sample_main: ./bin/grid.o
	$(CC) $(CFLAGS) -o ./sample_main.exe ./src/main.cpp ./src/grid.cpp ./include/grid.h 
	
	
all: ./bin/flipitDisplay.o ./bin/flipitEngine.o
	$(CC) $(CFLAGS) -o ./flipit.exe ./src/flipit.cpp $(SRC)

	
test: ./bin/flipitDisplay.o ./bin/flipitEngine.o
	$(CC) $(CFLAGS) -o ./test.exe ./test/flipit_test.cpp $(SRC)
	

	
	
./bin/flipitDisplay.o: ./src/flipitDisplay.cpp ./include/flipitDisplay.h
	$(CC) $(CFLAGS) -c ./src/flipitDisplay.cpp ./include/flipitDisplay.h -o ./bin/flipitDisplay.o

./bin/flipitEngine.o: ./src/flipitEngine.cpp ./include/flipitEngine.h
	$(CC) $(CFLAGS) -c ./src/flipitEngine.cpp ./include/flipitEngine.h -o ./bin/flipitDisplay.o
	
	
gridSample: ./bin/grid.o ./bin/gridSample.o
	$(CC) $(CFLAGS) -o ./gridSample.exe ./src/gridSamp.cpp ./src/flipitDisplay.cpp ./include/flipitDisplay.h ./src/grid.cpp ./include/grid.h 
	
./bin/gridSample.o: ./bin/grid.o ./src/gridSamp.cpp
	$(CC) $(CFLAGS) -c ./src/gridSamp.cpp -o ./bin/gridSample.o
	
	
./bin/grid.o: ./src/grid.cpp ./include/grid.h
	$(CC) $(CFLAGS) -c ./src/grid.cpp ./include/grid.h -o ./bin/grid.o

clean: 
	rm ./bin/*.o
	