cmake_minimum_required(VERSION 3.15)

set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CPP_COMPILER x86_64-w64-mingw32-g++)

project(Chessbot)

# Download and configure Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

set(SOURCES
    src/Board.cpp
    src/Brain.cpp
    src/Menu.cpp
    src/Program.cpp
    src/Move.cpp
)

# Copy neurons.txt to build directory
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/neurons.txt ${CMAKE_CURRENT_BINARY_DIR}/neurons.txt COPYONLY)

# Main executable
add_executable(Chessbot src/main.cpp ${SOURCES})
target_compile_features(Chessbot PUBLIC cxx_std_17)
target_compile_options(Chessbot PRIVATE -Wall -Wextra -pedantic)
target_include_directories(Chessbot PUBLIC include)

set(TESTS
    # tests/BoardTests.cpp
    tests/MoveTests.cpp
)

# Test executable
add_executable(ChessbotTests ${TESTS} ${SOURCES})
target_link_libraries(ChessbotTests PRIVATE GTest::gtest_main)
target_compile_features(ChessbotTests PUBLIC cxx_std_17)
target_compile_options(ChessbotTests PRIVATE -Wall -Wextra -pedantic)
target_include_directories(ChessbotTests PUBLIC include)

include(GoogleTest)
gtest_discover_tests(ChessbotTests)