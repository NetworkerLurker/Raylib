cmake_minimum_required(VERSION 3.23)
project (RPG)

set(CMAKE_CXX_STANDARD 20)
find_package(raylib 4.2 REQUIRED)
include_directories(/opt/homebrew/Cellar/raylib/4.2.0/include)
add_executable(RPG main.cpp Window.h Player.h InputHandler.cpp InputHandler.h Command.h Player.cpp)
target_link_libraries(RPG raylib)