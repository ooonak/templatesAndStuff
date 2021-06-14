cmake_minimum_required(VERSION 3.14)
project(SetGitHash CXX)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror -O3")

include(gitHash.cmake)

# Remember to add githash header and source file to sources.
set(SOURCES githash.h ${CMAKE_CURRENT_BINARY_DIR}/githash.cpp main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
