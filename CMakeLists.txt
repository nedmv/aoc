cmake_minimum_required(VERSION 3.12)
project(aoc2020 VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# TODO: get rid of GLOB.
# Proposed solution: regenerate CMakeLists.txt at day's init
file(GLOB_RECURSE src_2020 CONFIGURE_DEPENDS "2020/*.cpp")
file(GLOB_RECURSE src_2021 CONFIGURE_DEPENDS "2021/*.cpp")

add_executable(aoc main.cpp Task.cpp ${src_2020} ${src_2021})

execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/2020
                                                           ${CMAKE_BINARY_DIR}/2020)  
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/2021
                                                           ${CMAKE_BINARY_DIR}/2021)