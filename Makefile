# use `git update-index --no-assume-unchanged ./Makefile` to re-track this file.

.PHONY: clean test

all: directories bin/ut_all

TEST = $(shell ls ./test/**/*.h ./test/**/*.cpp)

SRC = $(shell ls ./src/**/*.h ./src/**/*.cpp)

OBJ = $(shell ls src/iterator/factory/*.cpp \
	| $(STRIP_PARENT_PATH) \
	| $(REPLACE_CPP_EXTENSION_WITH_O))
STRIP_PARENT_PATH = sed 's|src/iterator/factory/|obj/|g'
REPLACE_CPP_EXTENSION_WITH_O = sed 's|.cpp|.o|g'

COMPILE_ARGS = -O2 -std=gnu++17 -Wfatal-errors

bin/ut_all: test/ut_main.cpp $(OBJ) $(TEST) $(SRC)
	g++ -o $@ $< $(OBJ) $(COMPILE_ARGS) -lgtest -lpthread

obj/%.o: src/iterator/factory/%.cpp
	g++ -o $@ -c $< $(COMPILE_ARGS)

directories:
	mkdir -p bin

clean:
	rm -rf bin

test: all
	bin/ut_all
