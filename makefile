CFLAGS 		= -g -Wall -std=c++0x -I./include/ -I./lib/
CC 			= g++
SRC_ARRAY   = ./src/array.cpp
SRC_REFCNT	= ./src/refCounter.cpp ./include/refCounter.h
SRC_ALL 	= $(SRC_ARRAY) $(SRC_REFCNT)

test: refCounter.o
	$(CC) $(CFLAGS) ./src/array.spec.cpp $(SRC_REFCNT) -o ./bin/test
	./bin/test

h_test:
	$(CC) $(CFLAGS) ./src/hoffman.test.cpp  $(SRC_REFCNT) -o ./bin/h_test
	./bin/h_test

refCounter.o: $(SRC_REFCNT)
	$(CC) $(CFLAGS) -c $(SRC_REFCNT) -o ./bin/refCounter.o

clean:
	rm ./bin/*.o ./bin/*.exe ./*.exe -f