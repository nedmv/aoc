cmake_minimum_required(VERSION 3.12)
project(aoc2020 VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# file(GLOB aoc_src CONFIGURE_DEPENDS "*.hpp" "*.cpp")
# add_executable(aoc ${aoc_src})

add_executable(aoc main.cpp Task.cpp)

#TODO: Make this year independent.
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/2020
                                                           ${CMAKE_BINARY_DIR}/2020)