cmake_minimum_required(VERSION 3.10)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 11)
set(SFML_STATIC_LIBRARIES TRUE)
set(EXECUTABLE_NAME "Gameoflife")
set(SFML_DIR "/home/nico/Library/Frameworks/SFML251static")
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_executable(${EXECUTABLE_NAME} main.cpp GameOfLife.cpp GameOfLife.h)
target_link_libraries(${EXECUTABLE_NAME} sfml-system sfml-window sfml-graphics )