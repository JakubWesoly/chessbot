# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Kuba\dev\chessbot

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Kuba\dev\chessbot\build

# Include any dependencies generated for this target.
include CMakeFiles/ChessbotTests.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ChessbotTests.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ChessbotTests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ChessbotTests.dir/flags.make

CMakeFiles/ChessbotTests.dir/tests/BoardTests.cpp.obj: CMakeFiles/ChessbotTests.dir/flags.make
CMakeFiles/ChessbotTests.dir/tests/BoardTests.cpp.obj: CMakeFiles/ChessbotTests.dir/includes_CXX.rsp
CMakeFiles/ChessbotTests.dir/tests/BoardTests.cpp.obj: C:/Users/Kuba/dev/chessbot/tests/BoardTests.cpp
CMakeFiles/ChessbotTests.dir/tests/BoardTests.cpp.obj: CMakeFiles/ChessbotTests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Kuba\dev\chessbot\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ChessbotTests.dir/tests/BoardTests.cpp.obj"
	C:\ProgramData\mingw64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChessbotTests.dir/tests/BoardTests.cpp.obj -MF CMakeFiles\ChessbotTests.dir\tests\BoardTests.cpp.obj.d -o CMakeFiles\ChessbotTests.dir\tests\BoardTests.cpp.obj -c C:\Users\Kuba\dev\chessbot\tests\BoardTests.cpp

CMakeFiles/ChessbotTests.dir/tests/BoardTests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ChessbotTests.dir/tests/BoardTests.cpp.i"
	C:\ProgramData\mingw64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Kuba\dev\chessbot\tests\BoardTests.cpp > CMakeFiles\ChessbotTests.dir\tests\BoardTests.cpp.i

CMakeFiles/ChessbotTests.dir/tests/BoardTests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ChessbotTests.dir/tests/BoardTests.cpp.s"
	C:\ProgramData\mingw64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Kuba\dev\chessbot\tests\BoardTests.cpp -o CMakeFiles\ChessbotTests.dir\tests\BoardTests.cpp.s

CMakeFiles/ChessbotTests.dir/src/Board.cpp.obj: CMakeFiles/ChessbotTests.dir/flags.make
CMakeFiles/ChessbotTests.dir/src/Board.cpp.obj: CMakeFiles/ChessbotTests.dir/includes_CXX.rsp
CMakeFiles/ChessbotTests.dir/src/Board.cpp.obj: C:/Users/Kuba/dev/chessbot/src/Board.cpp
CMakeFiles/ChessbotTests.dir/src/Board.cpp.obj: CMakeFiles/ChessbotTests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Kuba\dev\chessbot\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ChessbotTests.dir/src/Board.cpp.obj"
	C:\ProgramData\mingw64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChessbotTests.dir/src/Board.cpp.obj -MF CMakeFiles\ChessbotTests.dir\src\Board.cpp.obj.d -o CMakeFiles\ChessbotTests.dir\src\Board.cpp.obj -c C:\Users\Kuba\dev\chessbot\src\Board.cpp

CMakeFiles/ChessbotTests.dir/src/Board.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ChessbotTests.dir/src/Board.cpp.i"
	C:\ProgramData\mingw64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Kuba\dev\chessbot\src\Board.cpp > CMakeFiles\ChessbotTests.dir\src\Board.cpp.i

CMakeFiles/ChessbotTests.dir/src/Board.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ChessbotTests.dir/src/Board.cpp.s"
	C:\ProgramData\mingw64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Kuba\dev\chessbot\src\Board.cpp -o CMakeFiles\ChessbotTests.dir\src\Board.cpp.s

CMakeFiles/ChessbotTests.dir/src/Brain.cpp.obj: CMakeFiles/ChessbotTests.dir/flags.make
CMakeFiles/ChessbotTests.dir/src/Brain.cpp.obj: CMakeFiles/ChessbotTests.dir/includes_CXX.rsp
CMakeFiles/ChessbotTests.dir/src/Brain.cpp.obj: C:/Users/Kuba/dev/chessbot/src/Brain.cpp
CMakeFiles/ChessbotTests.dir/src/Brain.cpp.obj: CMakeFiles/ChessbotTests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Kuba\dev\chessbot\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ChessbotTests.dir/src/Brain.cpp.obj"
	C:\ProgramData\mingw64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChessbotTests.dir/src/Brain.cpp.obj -MF CMakeFiles\ChessbotTests.dir\src\Brain.cpp.obj.d -o CMakeFiles\ChessbotTests.dir\src\Brain.cpp.obj -c C:\Users\Kuba\dev\chessbot\src\Brain.cpp

CMakeFiles/ChessbotTests.dir/src/Brain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ChessbotTests.dir/src/Brain.cpp.i"
	C:\ProgramData\mingw64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Kuba\dev\chessbot\src\Brain.cpp > CMakeFiles\ChessbotTests.dir\src\Brain.cpp.i

CMakeFiles/ChessbotTests.dir/src/Brain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ChessbotTests.dir/src/Brain.cpp.s"
	C:\ProgramData\mingw64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Kuba\dev\chessbot\src\Brain.cpp -o CMakeFiles\ChessbotTests.dir\src\Brain.cpp.s

CMakeFiles/ChessbotTests.dir/src/Menu.cpp.obj: CMakeFiles/ChessbotTests.dir/flags.make
CMakeFiles/ChessbotTests.dir/src/Menu.cpp.obj: CMakeFiles/ChessbotTests.dir/includes_CXX.rsp
CMakeFiles/ChessbotTests.dir/src/Menu.cpp.obj: C:/Users/Kuba/dev/chessbot/src/Menu.cpp
CMakeFiles/ChessbotTests.dir/src/Menu.cpp.obj: CMakeFiles/ChessbotTests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Kuba\dev\chessbot\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ChessbotTests.dir/src/Menu.cpp.obj"
	C:\ProgramData\mingw64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChessbotTests.dir/src/Menu.cpp.obj -MF CMakeFiles\ChessbotTests.dir\src\Menu.cpp.obj.d -o CMakeFiles\ChessbotTests.dir\src\Menu.cpp.obj -c C:\Users\Kuba\dev\chessbot\src\Menu.cpp

CMakeFiles/ChessbotTests.dir/src/Menu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ChessbotTests.dir/src/Menu.cpp.i"
	C:\ProgramData\mingw64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Kuba\dev\chessbot\src\Menu.cpp > CMakeFiles\ChessbotTests.dir\src\Menu.cpp.i

CMakeFiles/ChessbotTests.dir/src/Menu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ChessbotTests.dir/src/Menu.cpp.s"
	C:\ProgramData\mingw64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Kuba\dev\chessbot\src\Menu.cpp -o CMakeFiles\ChessbotTests.dir\src\Menu.cpp.s

CMakeFiles/ChessbotTests.dir/src/Program.cpp.obj: CMakeFiles/ChessbotTests.dir/flags.make
CMakeFiles/ChessbotTests.dir/src/Program.cpp.obj: CMakeFiles/ChessbotTests.dir/includes_CXX.rsp
CMakeFiles/ChessbotTests.dir/src/Program.cpp.obj: C:/Users/Kuba/dev/chessbot/src/Program.cpp
CMakeFiles/ChessbotTests.dir/src/Program.cpp.obj: CMakeFiles/ChessbotTests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Kuba\dev\chessbot\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ChessbotTests.dir/src/Program.cpp.obj"
	C:\ProgramData\mingw64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChessbotTests.dir/src/Program.cpp.obj -MF CMakeFiles\ChessbotTests.dir\src\Program.cpp.obj.d -o CMakeFiles\ChessbotTests.dir\src\Program.cpp.obj -c C:\Users\Kuba\dev\chessbot\src\Program.cpp

CMakeFiles/ChessbotTests.dir/src/Program.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ChessbotTests.dir/src/Program.cpp.i"
	C:\ProgramData\mingw64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Kuba\dev\chessbot\src\Program.cpp > CMakeFiles\ChessbotTests.dir\src\Program.cpp.i

CMakeFiles/ChessbotTests.dir/src/Program.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ChessbotTests.dir/src/Program.cpp.s"
	C:\ProgramData\mingw64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Kuba\dev\chessbot\src\Program.cpp -o CMakeFiles\ChessbotTests.dir\src\Program.cpp.s

CMakeFiles/ChessbotTests.dir/src/Move.cpp.obj: CMakeFiles/ChessbotTests.dir/flags.make
CMakeFiles/ChessbotTests.dir/src/Move.cpp.obj: CMakeFiles/ChessbotTests.dir/includes_CXX.rsp
CMakeFiles/ChessbotTests.dir/src/Move.cpp.obj: C:/Users/Kuba/dev/chessbot/src/Move.cpp
CMakeFiles/ChessbotTests.dir/src/Move.cpp.obj: CMakeFiles/ChessbotTests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Kuba\dev\chessbot\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/ChessbotTests.dir/src/Move.cpp.obj"
	C:\ProgramData\mingw64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChessbotTests.dir/src/Move.cpp.obj -MF CMakeFiles\ChessbotTests.dir\src\Move.cpp.obj.d -o CMakeFiles\ChessbotTests.dir\src\Move.cpp.obj -c C:\Users\Kuba\dev\chessbot\src\Move.cpp

CMakeFiles/ChessbotTests.dir/src/Move.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ChessbotTests.dir/src/Move.cpp.i"
	C:\ProgramData\mingw64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Kuba\dev\chessbot\src\Move.cpp > CMakeFiles\ChessbotTests.dir\src\Move.cpp.i

CMakeFiles/ChessbotTests.dir/src/Move.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ChessbotTests.dir/src/Move.cpp.s"
	C:\ProgramData\mingw64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Kuba\dev\chessbot\src\Move.cpp -o CMakeFiles\ChessbotTests.dir\src\Move.cpp.s

# Object files for target ChessbotTests
ChessbotTests_OBJECTS = \
"CMakeFiles/ChessbotTests.dir/tests/BoardTests.cpp.obj" \
"CMakeFiles/ChessbotTests.dir/src/Board.cpp.obj" \
"CMakeFiles/ChessbotTests.dir/src/Brain.cpp.obj" \
"CMakeFiles/ChessbotTests.dir/src/Menu.cpp.obj" \
"CMakeFiles/ChessbotTests.dir/src/Program.cpp.obj" \
"CMakeFiles/ChessbotTests.dir/src/Move.cpp.obj"

# External object files for target ChessbotTests
ChessbotTests_EXTERNAL_OBJECTS =

ChessbotTests.exe: CMakeFiles/ChessbotTests.dir/tests/BoardTests.cpp.obj
ChessbotTests.exe: CMakeFiles/ChessbotTests.dir/src/Board.cpp.obj
ChessbotTests.exe: CMakeFiles/ChessbotTests.dir/src/Brain.cpp.obj
ChessbotTests.exe: CMakeFiles/ChessbotTests.dir/src/Menu.cpp.obj
ChessbotTests.exe: CMakeFiles/ChessbotTests.dir/src/Program.cpp.obj
ChessbotTests.exe: CMakeFiles/ChessbotTests.dir/src/Move.cpp.obj
ChessbotTests.exe: CMakeFiles/ChessbotTests.dir/build.make
ChessbotTests.exe: lib/libgtest_main.a
ChessbotTests.exe: lib/libgtest.a
ChessbotTests.exe: CMakeFiles/ChessbotTests.dir/linkLibs.rsp
ChessbotTests.exe: CMakeFiles/ChessbotTests.dir/objects1.rsp
ChessbotTests.exe: CMakeFiles/ChessbotTests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\Kuba\dev\chessbot\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable ChessbotTests.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ChessbotTests.dir\link.txt --verbose=$(VERBOSE)
	"C:\Program Files\CMake\bin\cmake.exe" -D TEST_TARGET=ChessbotTests -D TEST_EXECUTABLE=C:/Users/Kuba/dev/chessbot/build/ChessbotTests.exe -D TEST_EXECUTOR= -D TEST_WORKING_DIR=C:/Users/Kuba/dev/chessbot/build -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_FILTER= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=ChessbotTests_TESTS -D CTEST_FILE=C:/Users/Kuba/dev/chessbot/build/ChessbotTests[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -D TEST_XML_OUTPUT_DIR= -P "C:/Program Files/CMake/share/cmake-3.30/Modules/GoogleTestAddTests.cmake"

# Rule to build all files generated by this target.
CMakeFiles/ChessbotTests.dir/build: ChessbotTests.exe
.PHONY : CMakeFiles/ChessbotTests.dir/build

CMakeFiles/ChessbotTests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ChessbotTests.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ChessbotTests.dir/clean

CMakeFiles/ChessbotTests.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Kuba\dev\chessbot C:\Users\Kuba\dev\chessbot C:\Users\Kuba\dev\chessbot\build C:\Users\Kuba\dev\chessbot\build C:\Users\Kuba\dev\chessbot\build\CMakeFiles\ChessbotTests.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/ChessbotTests.dir/depend

