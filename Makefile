# use `git update-index --no-assume-unchanged ./Makefile` to re-track this file.

.PHONY: clean

all: clean directories

TEST = $(shell ls ./test/**/*.h ./test/**/*.cpp)

TA_TEST = $(shell ls ./ta_test/**/*.h ./ta_test/**/*.cpp)

SRC = $(shell ls ./src/**/*.h ./src/**/*.cpp)

OBJ = $(shell ls src/iterator/factory/*.cpp \
	| $(STRIP_PARENT_PATH) \
	| $(REPLACE_CPP_EXTENSION_WITH_O))
STRIP_PARENT_PATH = sed 's|src/iterator/factory/|obj/|g'
REPLACE_CPP_EXTENSION_WITH_O = sed 's|.cpp|.o|g'

COMPILE_ARGS = -O2 -std=gnu++17 -Wfatal-errors

bin/ut_all: test/ut_main.cpp $(OBJ) $(TEST) $(SRC)
	g++ -o $@ $< $(OBJ) $(COMPILE_ARGS) -lgtest -lpthread # -fsanitize=address -g

bin/ut_all_ta: ta_test/ut_main.cpp $(OBJ) $(TA_TEST) $(SRC)
	g++ -o $@ $< $(OBJ) $(COMPILE_ARGS) -lgtest -lpthread # -fsanitize=address -g

obj/%.o: src/iterator/factory/%.cpp
	g++ -o $@ -c $< $(COMPILE_ARGS)

directories:
	mkdir -p bin obj

clean:
	rm -rf bin obj

test: all bin/ut_all
	bin/ut_all

test_ta: all bin/ut_all_ta
	bin/ut_all_ta

test_all: all bin/ut_all bin/ut_all_ta
	bin/ut_all
	bin/ut_all_ta

sync_gtest:
	git submodule update --init --recursive --remote --force --rebase
