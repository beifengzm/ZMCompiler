# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /home/zhangmeng/Sofrware/cmake-3.19.2-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/zhangmeng/Sofrware/cmake-3.19.2-Linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zhangmeng/myCode/compiler/nand2tetris/ZMComplier

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zhangmeng/myCode/compiler/nand2tetris/ZMComplier/build

# Include any dependencies generated for this target.
include CMakeFiles/IRTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/IRTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/IRTest.dir/flags.make

CMakeFiles/IRTest.dir/test/IRTest.c.o: CMakeFiles/IRTest.dir/flags.make
CMakeFiles/IRTest.dir/test/IRTest.c.o: ../test/IRTest.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhangmeng/myCode/compiler/nand2tetris/ZMComplier/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/IRTest.dir/test/IRTest.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/IRTest.dir/test/IRTest.c.o -c /home/zhangmeng/myCode/compiler/nand2tetris/ZMComplier/test/IRTest.c

CMakeFiles/IRTest.dir/test/IRTest.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/IRTest.dir/test/IRTest.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/zhangmeng/myCode/compiler/nand2tetris/ZMComplier/test/IRTest.c > CMakeFiles/IRTest.dir/test/IRTest.c.i

CMakeFiles/IRTest.dir/test/IRTest.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/IRTest.dir/test/IRTest.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/zhangmeng/myCode/compiler/nand2tetris/ZMComplier/test/IRTest.c -o CMakeFiles/IRTest.dir/test/IRTest.c.s

# Object files for target IRTest
IRTest_OBJECTS = \
"CMakeFiles/IRTest.dir/test/IRTest.c.o"

# External object files for target IRTest
IRTest_EXTERNAL_OBJECTS =

IRTest: CMakeFiles/IRTest.dir/test/IRTest.c.o
IRTest: CMakeFiles/IRTest.dir/build.make
IRTest: libfrontlib.a
IRTest: libtoollib.a
IRTest: CMakeFiles/IRTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zhangmeng/myCode/compiler/nand2tetris/ZMComplier/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable IRTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/IRTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/IRTest.dir/build: IRTest

.PHONY : CMakeFiles/IRTest.dir/build

CMakeFiles/IRTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/IRTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/IRTest.dir/clean

CMakeFiles/IRTest.dir/depend:
	cd /home/zhangmeng/myCode/compiler/nand2tetris/ZMComplier/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhangmeng/myCode/compiler/nand2tetris/ZMComplier /home/zhangmeng/myCode/compiler/nand2tetris/ZMComplier /home/zhangmeng/myCode/compiler/nand2tetris/ZMComplier/build /home/zhangmeng/myCode/compiler/nand2tetris/ZMComplier/build /home/zhangmeng/myCode/compiler/nand2tetris/ZMComplier/build/CMakeFiles/IRTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/IRTest.dir/depend

