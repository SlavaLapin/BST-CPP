# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /home/slava/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/183.4284.156/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/slava/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/183.4284.156/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/slava/MegaTreeProject/Workbench

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/slava/MegaTreeProject/Workbench/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Workbench.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Workbench.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Workbench.dir/flags.make

CMakeFiles/Workbench.dir/main.cpp.o: CMakeFiles/Workbench.dir/flags.make
CMakeFiles/Workbench.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/slava/MegaTreeProject/Workbench/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Workbench.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Workbench.dir/main.cpp.o -c /home/slava/MegaTreeProject/Workbench/main.cpp

CMakeFiles/Workbench.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Workbench.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/slava/MegaTreeProject/Workbench/main.cpp > CMakeFiles/Workbench.dir/main.cpp.i

CMakeFiles/Workbench.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Workbench.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/slava/MegaTreeProject/Workbench/main.cpp -o CMakeFiles/Workbench.dir/main.cpp.s

# Object files for target Workbench
Workbench_OBJECTS = \
"CMakeFiles/Workbench.dir/main.cpp.o"

# External object files for target Workbench
Workbench_EXTERNAL_OBJECTS =

Workbench: CMakeFiles/Workbench.dir/main.cpp.o
Workbench: CMakeFiles/Workbench.dir/build.make
Workbench: CMakeFiles/Workbench.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/slava/MegaTreeProject/Workbench/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Workbench"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Workbench.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Workbench.dir/build: Workbench

.PHONY : CMakeFiles/Workbench.dir/build

CMakeFiles/Workbench.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Workbench.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Workbench.dir/clean

CMakeFiles/Workbench.dir/depend:
	cd /home/slava/MegaTreeProject/Workbench/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/slava/MegaTreeProject/Workbench /home/slava/MegaTreeProject/Workbench /home/slava/MegaTreeProject/Workbench/cmake-build-debug /home/slava/MegaTreeProject/Workbench/cmake-build-debug /home/slava/MegaTreeProject/Workbench/cmake-build-debug/CMakeFiles/Workbench.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Workbench.dir/depend

