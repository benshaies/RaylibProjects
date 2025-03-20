cmake_minimum_required(VERSION 3.10)
project(RaylibGame C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-O3 -march=native -flto")

set(RAYLIB_PATH "/home/killswitch/raylib")

include_directories(${RAYLIB_PATH}/src)
link_directories(${RAYLIB_PATH}/src)
find_library(RAYLIB_LIB raylib HINTS ${RAYLIB_PATH}/src)

# Make sure to set the correct path to main.c
add_executable(game ../main.c)
target_link_libraries(game ${RAYLIB_LIB} GL m pthread dl rt X11)

