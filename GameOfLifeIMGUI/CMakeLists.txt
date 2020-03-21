cmake_minimum_required(VERSION 3.10)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 11)
set(SFML_STATIC_LIBRARIES TRUE)
set(EXECUTABLE_NAME "Gameoflife")
set(SFML_DIR "/home/nico/Library/Frameworks/SFML251static")
set(ImGui-SFML_DIR "/home/nico/Documents/imgui/localIMGUI")
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
find_package(ImGui-SFML REQUIRED)

add_executable(${EXECUTABLE_NAME} main.cpp GameOfLife.cpp GameOfLife.h)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ImGui-SFML::ImGui-SFML sfml-system sfml-window sfml-graphics )