# use `git update-index --no-assume-unchanged ./Makefile` to re-track this file.

.PHONY: clean # TODO: change to test_all.

all: test

prepare: clean directories

TEST = $(shell ls ./test/**/*.h)

TA_TEST = $(shell ls ./ta_test/**/*.h)

SRC = $(shell ls ./src/**/*.h)

GRAPHICS = $(shell ls ./src/graphics/**/*.h)

OBJ = $(shell ls src/iterator/factory/*.cpp \
	| $(STRIP_PARENT_PATH) \
	| $(REPLACE_CPP_EXTENSION_WITH_O))
STRIP_PARENT_PATH = sed 's|src/iterator/factory/|obj/|g'
REPLACE_CPP_EXTENSION_WITH_O = sed 's|.cpp|.o|g'

COMPILE_ARGS = -O0 -std=gnu++17 -Wfatal-errors
GOOGLETEST_ARGS = -lgtest -lpthread # -fsanitize=address -g
SDL2_ARGS = -lSDL2 -lSDL2_image

bin/ut_all: test/ut_main.cpp $(OBJ) $(TEST) $(SRC)
	export TESTER=self && g++ -o $@ $< $(OBJ) $(COMPILE_ARGS) $(GOOGLETEST_ARGS)

bin/ut_all_ta: ta_test/ut_main.cpp $(OBJ) $(TA_TEST) $(SRC)
	g++ -o $@ $< $(OBJ) $(COMPILE_ARGS) $(GOOGLETEST_ARGS)

bin/graphics: src/graphics.cpp $(OBJ) $(GRAPHICS) $(SRC)
	g++ -o $@ $< $(OBJ) $(COMPILE_ARGS) $(SDL2_ARGS)

obj/%.o: src/iterator/factory/%.cpp
	g++ -o $@ -c $< $(COMPILE_ARGS)

directories:
	mkdir -p bin obj

clean:
	rm -rf bin obj

test: prepare bin/ut_all
	export TESTER=self && bin/ut_all

test_ta: prepare bin/ut_all_ta
	bin/ut_all_ta

test_all: prepare bin/ut_all bin/ut_all_ta
	export TESTER=self && bin/ut_all
	bin/ut_all_ta

graphics: prepare bin/graphics
	bin/graphics ./input.txt

sync_gtest:
	git submodule update --init --recursive --remote --force --rebase

valgrind: CXXFLAGS += -O0 -g

VALGRIND_ARGS = \
	--tool=memcheck \
	--error-exitcode=1 \
	--track-origins=yes \
	--leak-check=full \
	--leak-resolution=high \
	--num-callers=50 \
	--show-leak-kinds=all \
	--show-error-list=yes

valgrind: clean prepare bin/ut_all
	export TESTER=self && valgrind $(VALGRIND_ARGS) bin/ut_all

valgrind_ta: clean prepare bin/ut_all_ta
	valgrind $(VALGRIND_ARGS) bin/ut_all_ta

# TODO: fix leak inside SDL's implementation (SDLRenderer) by SDLRenderer::init(int, int) 
valgrind_graphics: clean prepare bin/graphics
	export VALGRIND_MODE=true && valgrind $(VALGRIND_ARGS) bin/graphics ./input.txt
