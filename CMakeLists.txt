cmake_minimum_required(VERSION 3.0)
project(lolEloRating C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -lm")

set(CMAKE_C_STANDARD 99)

add_executable(lolEloRating main.c file.c file.h structs.c structs.h htmlcreator.c htmlcreator.h)

target_link_libraries(lolEloRating PRIVATE m)
