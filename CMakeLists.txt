cmake_minimum_required(VERSION 3.15)
project(Chessbot)
set(CMAKE_CXX_STANDARD 17)
set(SOURCES src/main.cpp src/Board.cpp src/Brain.cpp src/Menu.cpp src/Program.cpp src/Move.cpp)

add_executable(Chessbot ${SOURCES})
target_include_directories(Chessbot PUBLIC include)