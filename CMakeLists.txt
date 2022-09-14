cmake_minimum_required(VERSION 3.23)
project(posd2022f_108820003_hw)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)
include_directories(test)

set(SOURCE_FILES src/*.h src/*.cpp test/*.h test/*.cpp)

add_custom_target(
        RUN_ALL_TEST COMMAND make
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
