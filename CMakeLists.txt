cmake_minimum_required(VERSION 3.15)
project(Chessbot)

set(SOURCES
    src/main.cpp
    src/Board.cpp
    src/Brain.cpp
    src/Menu.cpp
    src/Program.cpp
    src/Move.cpp
    src/neurons.txt
)

add_executable(Chessbot ${SOURCES})

target_compile_features(Chessbot PUBLIC cxx_std_17)
target_compile_options(Chessbot PRIVATE -Wall -Wextra -pedantic)
target_include_directories(Chessbot PUBLIC include)
# target_link_libraries(Chessbot PRIVATE <library_name>)