# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gerasmark/daphne/io/TDMSpp-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gerasmark/daphne/io/TDMSpp-master

# Include any dependencies generated for this target.
include src/CMakeFiles/tdmspp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/tdmspp.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/tdmspp.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/tdmspp.dir/flags.make

src/CMakeFiles/tdmspp.dir/log.cpp.o: src/CMakeFiles/tdmspp.dir/flags.make
src/CMakeFiles/tdmspp.dir/log.cpp.o: src/log.cpp
src/CMakeFiles/tdmspp.dir/log.cpp.o: src/CMakeFiles/tdmspp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gerasmark/daphne/io/TDMSpp-master/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/tdmspp.dir/log.cpp.o"
	cd /home/gerasmark/daphne/io/TDMSpp-master/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/tdmspp.dir/log.cpp.o -MF CMakeFiles/tdmspp.dir/log.cpp.o.d -o CMakeFiles/tdmspp.dir/log.cpp.o -c /home/gerasmark/daphne/io/TDMSpp-master/src/log.cpp

src/CMakeFiles/tdmspp.dir/log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tdmspp.dir/log.cpp.i"
	cd /home/gerasmark/daphne/io/TDMSpp-master/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gerasmark/daphne/io/TDMSpp-master/src/log.cpp > CMakeFiles/tdmspp.dir/log.cpp.i

src/CMakeFiles/tdmspp.dir/log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tdmspp.dir/log.cpp.s"
	cd /home/gerasmark/daphne/io/TDMSpp-master/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gerasmark/daphne/io/TDMSpp-master/src/log.cpp -o CMakeFiles/tdmspp.dir/log.cpp.s

src/CMakeFiles/tdmspp.dir/tdms_file.cpp.o: src/CMakeFiles/tdmspp.dir/flags.make
src/CMakeFiles/tdmspp.dir/tdms_file.cpp.o: src/tdms_file.cpp
src/CMakeFiles/tdmspp.dir/tdms_file.cpp.o: src/CMakeFiles/tdmspp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gerasmark/daphne/io/TDMSpp-master/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/tdmspp.dir/tdms_file.cpp.o"
	cd /home/gerasmark/daphne/io/TDMSpp-master/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/tdmspp.dir/tdms_file.cpp.o -MF CMakeFiles/tdmspp.dir/tdms_file.cpp.o.d -o CMakeFiles/tdmspp.dir/tdms_file.cpp.o -c /home/gerasmark/daphne/io/TDMSpp-master/src/tdms_file.cpp

src/CMakeFiles/tdmspp.dir/tdms_file.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tdmspp.dir/tdms_file.cpp.i"
	cd /home/gerasmark/daphne/io/TDMSpp-master/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gerasmark/daphne/io/TDMSpp-master/src/tdms_file.cpp > CMakeFiles/tdmspp.dir/tdms_file.cpp.i

src/CMakeFiles/tdmspp.dir/tdms_file.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tdmspp.dir/tdms_file.cpp.s"
	cd /home/gerasmark/daphne/io/TDMSpp-master/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gerasmark/daphne/io/TDMSpp-master/src/tdms_file.cpp -o CMakeFiles/tdmspp.dir/tdms_file.cpp.s

src/CMakeFiles/tdmspp.dir/tdms_segment.cpp.o: src/CMakeFiles/tdmspp.dir/flags.make
src/CMakeFiles/tdmspp.dir/tdms_segment.cpp.o: src/tdms_segment.cpp
src/CMakeFiles/tdmspp.dir/tdms_segment.cpp.o: src/CMakeFiles/tdmspp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gerasmark/daphne/io/TDMSpp-master/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/tdmspp.dir/tdms_segment.cpp.o"
	cd /home/gerasmark/daphne/io/TDMSpp-master/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/tdmspp.dir/tdms_segment.cpp.o -MF CMakeFiles/tdmspp.dir/tdms_segment.cpp.o.d -o CMakeFiles/tdmspp.dir/tdms_segment.cpp.o -c /home/gerasmark/daphne/io/TDMSpp-master/src/tdms_segment.cpp

src/CMakeFiles/tdmspp.dir/tdms_segment.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tdmspp.dir/tdms_segment.cpp.i"
	cd /home/gerasmark/daphne/io/TDMSpp-master/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gerasmark/daphne/io/TDMSpp-master/src/tdms_segment.cpp > CMakeFiles/tdmspp.dir/tdms_segment.cpp.i

src/CMakeFiles/tdmspp.dir/tdms_segment.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tdmspp.dir/tdms_segment.cpp.s"
	cd /home/gerasmark/daphne/io/TDMSpp-master/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gerasmark/daphne/io/TDMSpp-master/src/tdms_segment.cpp -o CMakeFiles/tdmspp.dir/tdms_segment.cpp.s

# Object files for target tdmspp
tdmspp_OBJECTS = \
"CMakeFiles/tdmspp.dir/log.cpp.o" \
"CMakeFiles/tdmspp.dir/tdms_file.cpp.o" \
"CMakeFiles/tdmspp.dir/tdms_segment.cpp.o"

# External object files for target tdmspp
tdmspp_EXTERNAL_OBJECTS =

src/libtdmspp.a: src/CMakeFiles/tdmspp.dir/log.cpp.o
src/libtdmspp.a: src/CMakeFiles/tdmspp.dir/tdms_file.cpp.o
src/libtdmspp.a: src/CMakeFiles/tdmspp.dir/tdms_segment.cpp.o
src/libtdmspp.a: src/CMakeFiles/tdmspp.dir/build.make
src/libtdmspp.a: src/CMakeFiles/tdmspp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gerasmark/daphne/io/TDMSpp-master/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libtdmspp.a"
	cd /home/gerasmark/daphne/io/TDMSpp-master/src && $(CMAKE_COMMAND) -P CMakeFiles/tdmspp.dir/cmake_clean_target.cmake
	cd /home/gerasmark/daphne/io/TDMSpp-master/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tdmspp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/tdmspp.dir/build: src/libtdmspp.a
.PHONY : src/CMakeFiles/tdmspp.dir/build

src/CMakeFiles/tdmspp.dir/clean:
	cd /home/gerasmark/daphne/io/TDMSpp-master/src && $(CMAKE_COMMAND) -P CMakeFiles/tdmspp.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/tdmspp.dir/clean

src/CMakeFiles/tdmspp.dir/depend:
	cd /home/gerasmark/daphne/io/TDMSpp-master && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gerasmark/daphne/io/TDMSpp-master /home/gerasmark/daphne/io/TDMSpp-master/src /home/gerasmark/daphne/io/TDMSpp-master /home/gerasmark/daphne/io/TDMSpp-master/src /home/gerasmark/daphne/io/TDMSpp-master/src/CMakeFiles/tdmspp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/tdmspp.dir/depend

