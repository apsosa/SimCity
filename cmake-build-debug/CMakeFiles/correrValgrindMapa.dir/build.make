# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/clion-2019.1.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2019.1.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nowe/algo2-2020c1-grupal/tpg4/2020-c1-tp3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nowe/algo2-2020c1-grupal/tpg4/2020-c1-tp3/cmake-build-debug

# Utility rule file for correrValgrindMapa.

# Include the progress variables for this target.
include CMakeFiles/correrValgrindMapa.dir/progress.make

CMakeFiles/correrValgrindMapa: correrTestsMapa
	valgrind --leak-check=full -v ./correrTestsMapa 2>&1

correrValgrindMapa: CMakeFiles/correrValgrindMapa
correrValgrindMapa: CMakeFiles/correrValgrindMapa.dir/build.make

.PHONY : correrValgrindMapa

# Rule to build all files generated by this target.
CMakeFiles/correrValgrindMapa.dir/build: correrValgrindMapa

.PHONY : CMakeFiles/correrValgrindMapa.dir/build

CMakeFiles/correrValgrindMapa.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/correrValgrindMapa.dir/cmake_clean.cmake
.PHONY : CMakeFiles/correrValgrindMapa.dir/clean

CMakeFiles/correrValgrindMapa.dir/depend:
	cd /home/nowe/algo2-2020c1-grupal/tpg4/2020-c1-tp3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nowe/algo2-2020c1-grupal/tpg4/2020-c1-tp3 /home/nowe/algo2-2020c1-grupal/tpg4/2020-c1-tp3 /home/nowe/algo2-2020c1-grupal/tpg4/2020-c1-tp3/cmake-build-debug /home/nowe/algo2-2020c1-grupal/tpg4/2020-c1-tp3/cmake-build-debug /home/nowe/algo2-2020c1-grupal/tpg4/2020-c1-tp3/cmake-build-debug/CMakeFiles/correrValgrindMapa.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/correrValgrindMapa.dir/depend

