# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wth/catkin_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wth/catkin_ws/build

# Utility rule file for waterplus_map_tools_automoc.

# Include the progress variables for this target.
include waterplus_map_tools/CMakeFiles/waterplus_map_tools_automoc.dir/progress.make

waterplus_map_tools/CMakeFiles/waterplus_map_tools_automoc:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/wth/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic moc for target waterplus_map_tools"
	cd /home/wth/catkin_ws/build/waterplus_map_tools && /usr/bin/cmake -E cmake_autogen /home/wth/catkin_ws/build/waterplus_map_tools/CMakeFiles/waterplus_map_tools_automoc.dir/ ""

waterplus_map_tools_automoc: waterplus_map_tools/CMakeFiles/waterplus_map_tools_automoc
waterplus_map_tools_automoc: waterplus_map_tools/CMakeFiles/waterplus_map_tools_automoc.dir/build.make

.PHONY : waterplus_map_tools_automoc

# Rule to build all files generated by this target.
waterplus_map_tools/CMakeFiles/waterplus_map_tools_automoc.dir/build: waterplus_map_tools_automoc

.PHONY : waterplus_map_tools/CMakeFiles/waterplus_map_tools_automoc.dir/build

waterplus_map_tools/CMakeFiles/waterplus_map_tools_automoc.dir/clean:
	cd /home/wth/catkin_ws/build/waterplus_map_tools && $(CMAKE_COMMAND) -P CMakeFiles/waterplus_map_tools_automoc.dir/cmake_clean.cmake
.PHONY : waterplus_map_tools/CMakeFiles/waterplus_map_tools_automoc.dir/clean

waterplus_map_tools/CMakeFiles/waterplus_map_tools_automoc.dir/depend:
	cd /home/wth/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wth/catkin_ws/src /home/wth/catkin_ws/src/waterplus_map_tools /home/wth/catkin_ws/build /home/wth/catkin_ws/build/waterplus_map_tools /home/wth/catkin_ws/build/waterplus_map_tools/CMakeFiles/waterplus_map_tools_automoc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : waterplus_map_tools/CMakeFiles/waterplus_map_tools_automoc.dir/depend

