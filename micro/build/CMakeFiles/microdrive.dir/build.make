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
CMAKE_SOURCE_DIR = /home/m.lavaud/Documents/joystick_MCL/micro

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/m.lavaud/Documents/joystick_MCL/micro/build

# Include any dependencies generated for this target.
include CMakeFiles/microdrive.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/microdrive.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/microdrive.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/microdrive.dir/flags.make

CMakeFiles/microdrive.dir/microdrive_pybind.cpp.o: CMakeFiles/microdrive.dir/flags.make
CMakeFiles/microdrive.dir/microdrive_pybind.cpp.o: ../microdrive_pybind.cpp
CMakeFiles/microdrive.dir/microdrive_pybind.cpp.o: CMakeFiles/microdrive.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/m.lavaud/Documents/joystick_MCL/micro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/microdrive.dir/microdrive_pybind.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/microdrive.dir/microdrive_pybind.cpp.o -MF CMakeFiles/microdrive.dir/microdrive_pybind.cpp.o.d -o CMakeFiles/microdrive.dir/microdrive_pybind.cpp.o -c /home/m.lavaud/Documents/joystick_MCL/micro/microdrive_pybind.cpp

CMakeFiles/microdrive.dir/microdrive_pybind.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/microdrive.dir/microdrive_pybind.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/m.lavaud/Documents/joystick_MCL/micro/microdrive_pybind.cpp > CMakeFiles/microdrive.dir/microdrive_pybind.cpp.i

CMakeFiles/microdrive.dir/microdrive_pybind.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/microdrive.dir/microdrive_pybind.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/m.lavaud/Documents/joystick_MCL/micro/microdrive_pybind.cpp -o CMakeFiles/microdrive.dir/microdrive_pybind.cpp.s

# Object files for target microdrive
microdrive_OBJECTS = \
"CMakeFiles/microdrive.dir/microdrive_pybind.cpp.o"

# External object files for target microdrive
microdrive_EXTERNAL_OBJECTS =

microdrive.cpython-312-x86_64-linux-gnu.so: CMakeFiles/microdrive.dir/microdrive_pybind.cpp.o
microdrive.cpython-312-x86_64-linux-gnu.so: CMakeFiles/microdrive.dir/build.make
microdrive.cpython-312-x86_64-linux-gnu.so: /usr/lib/libmicrodrive.so
microdrive.cpython-312-x86_64-linux-gnu.so: CMakeFiles/microdrive.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/m.lavaud/Documents/joystick_MCL/micro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module microdrive.cpython-312-x86_64-linux-gnu.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/microdrive.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/microdrive.dir/build: microdrive.cpython-312-x86_64-linux-gnu.so
.PHONY : CMakeFiles/microdrive.dir/build

CMakeFiles/microdrive.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/microdrive.dir/cmake_clean.cmake
.PHONY : CMakeFiles/microdrive.dir/clean

CMakeFiles/microdrive.dir/depend:
	cd /home/m.lavaud/Documents/joystick_MCL/micro/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/m.lavaud/Documents/joystick_MCL/micro /home/m.lavaud/Documents/joystick_MCL/micro /home/m.lavaud/Documents/joystick_MCL/micro/build /home/m.lavaud/Documents/joystick_MCL/micro/build /home/m.lavaud/Documents/joystick_MCL/micro/build/CMakeFiles/microdrive.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/microdrive.dir/depend
