# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.27.6/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.27.6/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/pirko/Documents/hku/jaar2/csd/CSD2d

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/pirko/Documents/hku/jaar2/csd/CSD2d/build

# Utility rule file for p1_All.

# Include any custom commands dependencies for this target.
include p1/CMakeFiles/p1_All.dir/compiler_depend.make

# Include the progress variables for this target.
include p1/CMakeFiles/p1_All.dir/progress.make

p1_All: p1/CMakeFiles/p1_All.dir/build.make
.PHONY : p1_All

# Rule to build all files generated by this target.
p1/CMakeFiles/p1_All.dir/build: p1_All
.PHONY : p1/CMakeFiles/p1_All.dir/build

p1/CMakeFiles/p1_All.dir/clean:
	cd /Users/pirko/Documents/hku/jaar2/csd/CSD2d/build/p1 && $(CMAKE_COMMAND) -P CMakeFiles/p1_All.dir/cmake_clean.cmake
.PHONY : p1/CMakeFiles/p1_All.dir/clean

p1/CMakeFiles/p1_All.dir/depend:
	cd /Users/pirko/Documents/hku/jaar2/csd/CSD2d/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/pirko/Documents/hku/jaar2/csd/CSD2d /Users/pirko/Documents/hku/jaar2/csd/CSD2d/p1 /Users/pirko/Documents/hku/jaar2/csd/CSD2d/build /Users/pirko/Documents/hku/jaar2/csd/CSD2d/build/p1 /Users/pirko/Documents/hku/jaar2/csd/CSD2d/build/p1/CMakeFiles/p1_All.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : p1/CMakeFiles/p1_All.dir/depend

