cmake_minimum_required(VERSION 3.10)

project(Watchy)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)

add_subdirectory(bluez_inc)

add_executable(Watchy src/main.c src/kissinger2.c)
target_link_libraries(Watchy PRIVATE SDL2::SDL2 Binc)
