# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.28

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\MyProjects\TFT\TFT-PerfectTraits

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\MyProjects\TFT\TFT-PerfectTraits\build

# Include any dependencies generated for this target.
include CMakeFiles/PerfectTraits.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/PerfectTraits.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/PerfectTraits.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PerfectTraits.dir/flags.make

CMakeFiles/PerfectTraits.dir/src/main.cpp.obj: CMakeFiles/PerfectTraits.dir/flags.make
CMakeFiles/PerfectTraits.dir/src/main.cpp.obj: CMakeFiles/PerfectTraits.dir/includes_CXX.rsp
CMakeFiles/PerfectTraits.dir/src/main.cpp.obj: D:/MyProjects/TFT/TFT-PerfectTraits/src/main.cpp
CMakeFiles/PerfectTraits.dir/src/main.cpp.obj: CMakeFiles/PerfectTraits.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\MyProjects\TFT\TFT-PerfectTraits\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PerfectTraits.dir/src/main.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PerfectTraits.dir/src/main.cpp.obj -MF CMakeFiles\PerfectTraits.dir\src\main.cpp.obj.d -o CMakeFiles\PerfectTraits.dir\src\main.cpp.obj -c D:\MyProjects\TFT\TFT-PerfectTraits\src\main.cpp

CMakeFiles/PerfectTraits.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/PerfectTraits.dir/src/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\MyProjects\TFT\TFT-PerfectTraits\src\main.cpp > CMakeFiles\PerfectTraits.dir\src\main.cpp.i

CMakeFiles/PerfectTraits.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/PerfectTraits.dir/src/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\MyProjects\TFT\TFT-PerfectTraits\src\main.cpp -o CMakeFiles\PerfectTraits.dir\src\main.cpp.s

CMakeFiles/PerfectTraits.dir/src/ParseCSV.cpp.obj: CMakeFiles/PerfectTraits.dir/flags.make
CMakeFiles/PerfectTraits.dir/src/ParseCSV.cpp.obj: CMakeFiles/PerfectTraits.dir/includes_CXX.rsp
CMakeFiles/PerfectTraits.dir/src/ParseCSV.cpp.obj: D:/MyProjects/TFT/TFT-PerfectTraits/src/ParseCSV.cpp
CMakeFiles/PerfectTraits.dir/src/ParseCSV.cpp.obj: CMakeFiles/PerfectTraits.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\MyProjects\TFT\TFT-PerfectTraits\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PerfectTraits.dir/src/ParseCSV.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PerfectTraits.dir/src/ParseCSV.cpp.obj -MF CMakeFiles\PerfectTraits.dir\src\ParseCSV.cpp.obj.d -o CMakeFiles\PerfectTraits.dir\src\ParseCSV.cpp.obj -c D:\MyProjects\TFT\TFT-PerfectTraits\src\ParseCSV.cpp

CMakeFiles/PerfectTraits.dir/src/ParseCSV.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/PerfectTraits.dir/src/ParseCSV.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\MyProjects\TFT\TFT-PerfectTraits\src\ParseCSV.cpp > CMakeFiles\PerfectTraits.dir\src\ParseCSV.cpp.i

CMakeFiles/PerfectTraits.dir/src/ParseCSV.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/PerfectTraits.dir/src/ParseCSV.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\MyProjects\TFT\TFT-PerfectTraits\src\ParseCSV.cpp -o CMakeFiles\PerfectTraits.dir\src\ParseCSV.cpp.s

CMakeFiles/PerfectTraits.dir/src/Unit.cpp.obj: CMakeFiles/PerfectTraits.dir/flags.make
CMakeFiles/PerfectTraits.dir/src/Unit.cpp.obj: CMakeFiles/PerfectTraits.dir/includes_CXX.rsp
CMakeFiles/PerfectTraits.dir/src/Unit.cpp.obj: D:/MyProjects/TFT/TFT-PerfectTraits/src/Unit.cpp
CMakeFiles/PerfectTraits.dir/src/Unit.cpp.obj: CMakeFiles/PerfectTraits.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\MyProjects\TFT\TFT-PerfectTraits\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/PerfectTraits.dir/src/Unit.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PerfectTraits.dir/src/Unit.cpp.obj -MF CMakeFiles\PerfectTraits.dir\src\Unit.cpp.obj.d -o CMakeFiles\PerfectTraits.dir\src\Unit.cpp.obj -c D:\MyProjects\TFT\TFT-PerfectTraits\src\Unit.cpp

CMakeFiles/PerfectTraits.dir/src/Unit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/PerfectTraits.dir/src/Unit.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\MyProjects\TFT\TFT-PerfectTraits\src\Unit.cpp > CMakeFiles\PerfectTraits.dir\src\Unit.cpp.i

CMakeFiles/PerfectTraits.dir/src/Unit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/PerfectTraits.dir/src/Unit.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\MyProjects\TFT\TFT-PerfectTraits\src\Unit.cpp -o CMakeFiles\PerfectTraits.dir\src\Unit.cpp.s

CMakeFiles/PerfectTraits.dir/src/UnitController.cpp.obj: CMakeFiles/PerfectTraits.dir/flags.make
CMakeFiles/PerfectTraits.dir/src/UnitController.cpp.obj: CMakeFiles/PerfectTraits.dir/includes_CXX.rsp
CMakeFiles/PerfectTraits.dir/src/UnitController.cpp.obj: D:/MyProjects/TFT/TFT-PerfectTraits/src/UnitController.cpp
CMakeFiles/PerfectTraits.dir/src/UnitController.cpp.obj: CMakeFiles/PerfectTraits.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\MyProjects\TFT\TFT-PerfectTraits\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/PerfectTraits.dir/src/UnitController.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PerfectTraits.dir/src/UnitController.cpp.obj -MF CMakeFiles\PerfectTraits.dir\src\UnitController.cpp.obj.d -o CMakeFiles\PerfectTraits.dir\src\UnitController.cpp.obj -c D:\MyProjects\TFT\TFT-PerfectTraits\src\UnitController.cpp

CMakeFiles/PerfectTraits.dir/src/UnitController.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/PerfectTraits.dir/src/UnitController.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\MyProjects\TFT\TFT-PerfectTraits\src\UnitController.cpp > CMakeFiles\PerfectTraits.dir\src\UnitController.cpp.i

CMakeFiles/PerfectTraits.dir/src/UnitController.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/PerfectTraits.dir/src/UnitController.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\MyProjects\TFT\TFT-PerfectTraits\src\UnitController.cpp -o CMakeFiles\PerfectTraits.dir\src\UnitController.cpp.s

# Object files for target PerfectTraits
PerfectTraits_OBJECTS = \
"CMakeFiles/PerfectTraits.dir/src/main.cpp.obj" \
"CMakeFiles/PerfectTraits.dir/src/ParseCSV.cpp.obj" \
"CMakeFiles/PerfectTraits.dir/src/Unit.cpp.obj" \
"CMakeFiles/PerfectTraits.dir/src/UnitController.cpp.obj"

# External object files for target PerfectTraits
PerfectTraits_EXTERNAL_OBJECTS =

PerfectTraits.exe: CMakeFiles/PerfectTraits.dir/src/main.cpp.obj
PerfectTraits.exe: CMakeFiles/PerfectTraits.dir/src/ParseCSV.cpp.obj
PerfectTraits.exe: CMakeFiles/PerfectTraits.dir/src/Unit.cpp.obj
PerfectTraits.exe: CMakeFiles/PerfectTraits.dir/src/UnitController.cpp.obj
PerfectTraits.exe: CMakeFiles/PerfectTraits.dir/build.make
PerfectTraits.exe: CMakeFiles/PerfectTraits.dir/linkLibs.rsp
PerfectTraits.exe: CMakeFiles/PerfectTraits.dir/objects1.rsp
PerfectTraits.exe: CMakeFiles/PerfectTraits.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\MyProjects\TFT\TFT-PerfectTraits\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable PerfectTraits.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\PerfectTraits.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PerfectTraits.dir/build: PerfectTraits.exe
.PHONY : CMakeFiles/PerfectTraits.dir/build

CMakeFiles/PerfectTraits.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\PerfectTraits.dir\cmake_clean.cmake
.PHONY : CMakeFiles/PerfectTraits.dir/clean

CMakeFiles/PerfectTraits.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\MyProjects\TFT\TFT-PerfectTraits D:\MyProjects\TFT\TFT-PerfectTraits D:\MyProjects\TFT\TFT-PerfectTraits\build D:\MyProjects\TFT\TFT-PerfectTraits\build D:\MyProjects\TFT\TFT-PerfectTraits\build\CMakeFiles\PerfectTraits.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/PerfectTraits.dir/depend

