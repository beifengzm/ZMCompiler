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
include CMakeFiles/toollib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/toollib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/toollib.dir/flags.make

CMakeFiles/toollib.dir/src/tools/Hash.c.o: CMakeFiles/toollib.dir/flags.make
CMakeFiles/toollib.dir/src/tools/Hash.c.o: ../src/tools/Hash.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhangmeng/myCode/compiler/nand2tetris/ZMComplier/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/toollib.dir/src/tools/Hash.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/toollib.dir/src/tools/Hash.c.o -c /home/zhangmeng/myCode/compiler/nand2tetris/ZMComplier/src/tools/Hash.c

CMakeFiles/toollib.dir/src/tools/Hash.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/toollib.dir/src/tools/Hash.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/zhangmeng/myCode/compiler/nand2tetris/ZMComplier/src/tools/Hash.c > CMakeFiles/toollib.dir/src/tools/Hash.c.i

CMakeFiles/toollib.dir/src/tools/Hash.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/toollib.dir/src/tools/Hash.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/zhangmeng/myCode/compiler/nand2tetris/ZMComplier/src/tools/Hash.c -o CMakeFiles/toollib.dir/src/tools/Hash.c.s

# Object files for target toollib
toollib_OBJECTS = \
"CMakeFiles/toollib.dir/src/tools/Hash.c.o"

# External object files for target toollib
toollib_EXTERNAL_OBJECTS =

libtoollib.a: CMakeFiles/toollib.dir/src/tools/Hash.c.o
libtoollib.a: CMakeFiles/toollib.dir/build.make
libtoollib.a: CMakeFiles/toollib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zhangmeng/myCode/compiler/nand2tetris/ZMComplier/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libtoollib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/toollib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/toollib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/toollib.dir/build: libtoollib.a

.PHONY : CMakeFiles/toollib.dir/build

CMakeFiles/toollib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/toollib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/toollib.dir/clean

CMakeFiles/toollib.dir/depend:
	cd /home/zhangmeng/myCode/compiler/nand2tetris/ZMComplier/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhangmeng/myCode/compiler/nand2tetris/ZMComplier /home/zhangmeng/myCode/compiler/nand2tetris/ZMComplier /home/zhangmeng/myCode/compiler/nand2tetris/ZMComplier/build /home/zhangmeng/myCode/compiler/nand2tetris/ZMComplier/build /home/zhangmeng/myCode/compiler/nand2tetris/ZMComplier/build/CMakeFiles/toollib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/toollib.dir/depend
