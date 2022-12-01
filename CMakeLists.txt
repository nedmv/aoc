cmake_minimum_required(VERSION 3.12)
project(aoc2020 VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# TODO: get rid of GLOB.
# Proposed solution: regenerate CMakeLists.txt at day's init
file(GLOB_RECURSE src CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE puzzles CONFIGURE_DEPENDS "puzzles/*.cpp")

add_executable(aoc ${src} ${puzzles})

execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/puzzles
                                                           ${CMAKE_BINARY_DIR}/puzzles)                                                         
