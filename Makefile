.PHONY: clean test

all: directories ut_main

TEST = $(shell ls ./test/**/*.h ./test/**/*.cpp)

SRC = $(shell ls ./src/**/*.h ./src/**/*.cpp)

ut_main: test/ut_main.cpp $(TEST) $(SRC)
	# Note that the latest version of g++ std currently is 'gnu++2b'.
	# However, the latest version of g++ on the server is 'gnu++2a', so we use 'gnu++2a' here.
	g++ -O2 -std=gnu++2a test/ut_main.cpp -o bin/ut_all -lgtest -lpthread

directories:
	mkdir -p bin

clean:
	rm -rf bin

test: all
	bin/ut_all
