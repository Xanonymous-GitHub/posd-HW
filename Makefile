.PHONY: clean test

all: directories ut_main

TEST = $(shell ls ./test/**/*.h ./test/**/*.cpp)

SRC = $(shell ls ./src/**/*.h ./src/**/*.cpp)

ut_main: test/ut_main.cpp $(TEST) $(SRC)
	g++ -O2 -std=c++2a test/ut_main.cpp -o bin/ut_all -lgtest -lpthread

directories:
	mkdir -p bin

clean:
	rm -rf bin

test: all
	bin/ut_all
