# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/gustavnielsen/Documents/Kode.nosync/chess/build

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/gustavnielsen/Documents/Kode.nosync/chess

# Include any dependencies generated for this target.
include CMakeFiles/chess.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/chess.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/chess.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/chess.dir/flags.make

CMakeFiles/chess.dir/chess.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/chess.cpp.o: chess.cpp
CMakeFiles/chess.dir/chess.cpp.o: CMakeFiles/chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/gustavnielsen/Documents/Kode.nosync/chess/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/chess.dir/chess.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess.dir/chess.cpp.o -MF CMakeFiles/chess.dir/chess.cpp.o.d -o CMakeFiles/chess.dir/chess.cpp.o -c /Users/gustavnielsen/Documents/Kode.nosync/chess/chess.cpp

CMakeFiles/chess.dir/chess.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess.dir/chess.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gustavnielsen/Documents/Kode.nosync/chess/chess.cpp > CMakeFiles/chess.dir/chess.cpp.i

CMakeFiles/chess.dir/chess.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess.dir/chess.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gustavnielsen/Documents/Kode.nosync/chess/chess.cpp -o CMakeFiles/chess.dir/chess.cpp.s

CMakeFiles/chess.dir/test.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/test.cpp.o: test.cpp
CMakeFiles/chess.dir/test.cpp.o: CMakeFiles/chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/gustavnielsen/Documents/Kode.nosync/chess/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/chess.dir/test.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess.dir/test.cpp.o -MF CMakeFiles/chess.dir/test.cpp.o.d -o CMakeFiles/chess.dir/test.cpp.o -c /Users/gustavnielsen/Documents/Kode.nosync/chess/test.cpp

CMakeFiles/chess.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess.dir/test.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gustavnielsen/Documents/Kode.nosync/chess/test.cpp > CMakeFiles/chess.dir/test.cpp.i

CMakeFiles/chess.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess.dir/test.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gustavnielsen/Documents/Kode.nosync/chess/test.cpp -o CMakeFiles/chess.dir/test.cpp.s

CMakeFiles/chess.dir/gui.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/gui.cpp.o: gui.cpp
CMakeFiles/chess.dir/gui.cpp.o: CMakeFiles/chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/gustavnielsen/Documents/Kode.nosync/chess/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/chess.dir/gui.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess.dir/gui.cpp.o -MF CMakeFiles/chess.dir/gui.cpp.o.d -o CMakeFiles/chess.dir/gui.cpp.o -c /Users/gustavnielsen/Documents/Kode.nosync/chess/gui.cpp

CMakeFiles/chess.dir/gui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess.dir/gui.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gustavnielsen/Documents/Kode.nosync/chess/gui.cpp > CMakeFiles/chess.dir/gui.cpp.i

CMakeFiles/chess.dir/gui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess.dir/gui.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gustavnielsen/Documents/Kode.nosync/chess/gui.cpp -o CMakeFiles/chess.dir/gui.cpp.s

CMakeFiles/chess.dir/PieceLoader.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/PieceLoader.cpp.o: PieceLoader.cpp
CMakeFiles/chess.dir/PieceLoader.cpp.o: CMakeFiles/chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/gustavnielsen/Documents/Kode.nosync/chess/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/chess.dir/PieceLoader.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess.dir/PieceLoader.cpp.o -MF CMakeFiles/chess.dir/PieceLoader.cpp.o.d -o CMakeFiles/chess.dir/PieceLoader.cpp.o -c /Users/gustavnielsen/Documents/Kode.nosync/chess/PieceLoader.cpp

CMakeFiles/chess.dir/PieceLoader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess.dir/PieceLoader.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gustavnielsen/Documents/Kode.nosync/chess/PieceLoader.cpp > CMakeFiles/chess.dir/PieceLoader.cpp.i

CMakeFiles/chess.dir/PieceLoader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess.dir/PieceLoader.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gustavnielsen/Documents/Kode.nosync/chess/PieceLoader.cpp -o CMakeFiles/chess.dir/PieceLoader.cpp.s

# Object files for target chess
chess_OBJECTS = \
"CMakeFiles/chess.dir/chess.cpp.o" \
"CMakeFiles/chess.dir/test.cpp.o" \
"CMakeFiles/chess.dir/gui.cpp.o" \
"CMakeFiles/chess.dir/PieceLoader.cpp.o"

# External object files for target chess
chess_EXTERNAL_OBJECTS =

chess: CMakeFiles/chess.dir/chess.cpp.o
chess: CMakeFiles/chess.dir/test.cpp.o
chess: CMakeFiles/chess.dir/gui.cpp.o
chess: CMakeFiles/chess.dir/PieceLoader.cpp.o
chess: CMakeFiles/chess.dir/build.make
chess: /opt/homebrew/opt/sfml@2/lib/libsfml-graphics.2.6.2.dylib
chess: /opt/homebrew/opt/sfml@2/lib/libsfml-window.2.6.2.dylib
chess: /opt/homebrew/opt/sfml@2/lib/libsfml-system.2.6.2.dylib
chess: CMakeFiles/chess.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/gustavnielsen/Documents/Kode.nosync/chess/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable chess"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/chess.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/chess.dir/build: chess
.PHONY : CMakeFiles/chess.dir/build

CMakeFiles/chess.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/chess.dir/cmake_clean.cmake
.PHONY : CMakeFiles/chess.dir/clean

CMakeFiles/chess.dir/depend:
	cd /Users/gustavnielsen/Documents/Kode.nosync/chess && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/gustavnielsen/Documents/Kode.nosync/chess/build /Users/gustavnielsen/Documents/Kode.nosync/chess/build /Users/gustavnielsen/Documents/Kode.nosync/chess /Users/gustavnielsen/Documents/Kode.nosync/chess /Users/gustavnielsen/Documents/Kode.nosync/chess/CMakeFiles/chess.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/chess.dir/depend

