# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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
CMAKE_COMMAND = /cvmfs/cepc.ihep.ac.cn/software/cepcsoft/x86_64-centos7-gcc49/external/CMake/2.8.5/install/bin/cmake

# The command to remove a file.
RM = /cvmfs/cepc.ihep.ac.cn/software/cepcsoft/x86_64-centos7-gcc49/external/CMake/2.8.5/install/bin/cmake -E remove -f

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /workfs2/cepc/xuliang/processor/GenJet/FSClasser

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workfs2/cepc/xuliang/processor/GenJet/FSClasser/build

# Utility rule file for NightlyStart.

CMakeFiles/NightlyStart:
	/cvmfs/cepc.ihep.ac.cn/software/cepcsoft/x86_64-centos7-gcc49/external/CMake/2.8.5/install/bin/ctest -D NightlyStart

NightlyStart: CMakeFiles/NightlyStart
NightlyStart: CMakeFiles/NightlyStart.dir/build.make
.PHONY : NightlyStart

# Rule to build all files generated by this target.
CMakeFiles/NightlyStart.dir/build: NightlyStart
.PHONY : CMakeFiles/NightlyStart.dir/build

CMakeFiles/NightlyStart.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/NightlyStart.dir/cmake_clean.cmake
.PHONY : CMakeFiles/NightlyStart.dir/clean

CMakeFiles/NightlyStart.dir/depend:
	cd /workfs2/cepc/xuliang/processor/GenJet/FSClasser/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workfs2/cepc/xuliang/processor/GenJet/FSClasser /workfs2/cepc/xuliang/processor/GenJet/FSClasser /workfs2/cepc/xuliang/processor/GenJet/FSClasser/build /workfs2/cepc/xuliang/processor/GenJet/FSClasser/build /workfs2/cepc/xuliang/processor/GenJet/FSClasser/build/CMakeFiles/NightlyStart.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/NightlyStart.dir/depend

