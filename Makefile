# use `git update-index --no-assume-unchanged ./Makefile` to re-track this file.

.PHONY: clean test

all: directories ut_main

TEST = $(shell ls ./test/**/*.h ./test/**/*.cpp)

SRC = $(shell ls ./src/**/*.h ./src/**/*.cpp)

COMPILE_ARGS = -O2 -std=gnu++2a test/ut_main.cpp -o bin/ut_all -lgtest -lpthread -fconcepts

# Don't use this for now, it's not working, just for fun.
COMPILE_ARGS_ME = -O2 -std=gnu++17 test/ut_main.cpp -o bin/ut_all -lgtest -lpthread

ut_main: test/ut_main.cpp $(TEST) $(SRC)
	# Note that the latest version of g++ std currently is 'gnu++2b'.
	# However, the latest version of g++ on the server is 'gnu++2a', so we use 'gnu++2a' here.

	g++ $(COMPILE_ARGS_ME)

directories:
	mkdir -p bin

clean:
	rm -rf bin

test: all
	bin/ut_all
