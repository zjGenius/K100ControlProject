# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/zhangjun/code/K100ControlProject/libCreate

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zhangjun/code/K100ControlProject/libCreate/build

# Include any dependencies generated for this target.
include CMakeFiles/peripheral.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/peripheral.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/peripheral.dir/flags.make

CMakeFiles/peripheral.dir/src/SDR/buffer.o: CMakeFiles/peripheral.dir/flags.make
CMakeFiles/peripheral.dir/src/SDR/buffer.o: ../src/SDR/buffer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhangjun/code/K100ControlProject/libCreate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/peripheral.dir/src/SDR/buffer.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/peripheral.dir/src/SDR/buffer.o -c /home/zhangjun/code/K100ControlProject/libCreate/src/SDR/buffer.cpp

CMakeFiles/peripheral.dir/src/SDR/buffer.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/peripheral.dir/src/SDR/buffer.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhangjun/code/K100ControlProject/libCreate/src/SDR/buffer.cpp > CMakeFiles/peripheral.dir/src/SDR/buffer.i

CMakeFiles/peripheral.dir/src/SDR/buffer.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/peripheral.dir/src/SDR/buffer.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhangjun/code/K100ControlProject/libCreate/src/SDR/buffer.cpp -o CMakeFiles/peripheral.dir/src/SDR/buffer.s

CMakeFiles/peripheral.dir/src/SDR/context.o: CMakeFiles/peripheral.dir/flags.make
CMakeFiles/peripheral.dir/src/SDR/context.o: ../src/SDR/context.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhangjun/code/K100ControlProject/libCreate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/peripheral.dir/src/SDR/context.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/peripheral.dir/src/SDR/context.o -c /home/zhangjun/code/K100ControlProject/libCreate/src/SDR/context.cpp

CMakeFiles/peripheral.dir/src/SDR/context.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/peripheral.dir/src/SDR/context.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhangjun/code/K100ControlProject/libCreate/src/SDR/context.cpp > CMakeFiles/peripheral.dir/src/SDR/context.i

CMakeFiles/peripheral.dir/src/SDR/context.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/peripheral.dir/src/SDR/context.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhangjun/code/K100ControlProject/libCreate/src/SDR/context.cpp -o CMakeFiles/peripheral.dir/src/SDR/context.s

CMakeFiles/peripheral.dir/src/SDR/device.o: CMakeFiles/peripheral.dir/flags.make
CMakeFiles/peripheral.dir/src/SDR/device.o: ../src/SDR/device.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhangjun/code/K100ControlProject/libCreate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/peripheral.dir/src/SDR/device.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/peripheral.dir/src/SDR/device.o -c /home/zhangjun/code/K100ControlProject/libCreate/src/SDR/device.cpp

CMakeFiles/peripheral.dir/src/SDR/device.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/peripheral.dir/src/SDR/device.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhangjun/code/K100ControlProject/libCreate/src/SDR/device.cpp > CMakeFiles/peripheral.dir/src/SDR/device.i

CMakeFiles/peripheral.dir/src/SDR/device.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/peripheral.dir/src/SDR/device.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhangjun/code/K100ControlProject/libCreate/src/SDR/device.cpp -o CMakeFiles/peripheral.dir/src/SDR/device.s

CMakeFiles/peripheral.dir/src/SDR/rxstream.o: CMakeFiles/peripheral.dir/flags.make
CMakeFiles/peripheral.dir/src/SDR/rxstream.o: ../src/SDR/rxstream.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhangjun/code/K100ControlProject/libCreate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/peripheral.dir/src/SDR/rxstream.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/peripheral.dir/src/SDR/rxstream.o -c /home/zhangjun/code/K100ControlProject/libCreate/src/SDR/rxstream.cpp

CMakeFiles/peripheral.dir/src/SDR/rxstream.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/peripheral.dir/src/SDR/rxstream.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhangjun/code/K100ControlProject/libCreate/src/SDR/rxstream.cpp > CMakeFiles/peripheral.dir/src/SDR/rxstream.i

CMakeFiles/peripheral.dir/src/SDR/rxstream.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/peripheral.dir/src/SDR/rxstream.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhangjun/code/K100ControlProject/libCreate/src/SDR/rxstream.cpp -o CMakeFiles/peripheral.dir/src/SDR/rxstream.s

CMakeFiles/peripheral.dir/src/IIORegister.o: CMakeFiles/peripheral.dir/flags.make
CMakeFiles/peripheral.dir/src/IIORegister.o: ../src/IIORegister.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhangjun/code/K100ControlProject/libCreate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/peripheral.dir/src/IIORegister.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/peripheral.dir/src/IIORegister.o -c /home/zhangjun/code/K100ControlProject/libCreate/src/IIORegister.cpp

CMakeFiles/peripheral.dir/src/IIORegister.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/peripheral.dir/src/IIORegister.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhangjun/code/K100ControlProject/libCreate/src/IIORegister.cpp > CMakeFiles/peripheral.dir/src/IIORegister.i

CMakeFiles/peripheral.dir/src/IIORegister.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/peripheral.dir/src/IIORegister.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhangjun/code/K100ControlProject/libCreate/src/IIORegister.cpp -o CMakeFiles/peripheral.dir/src/IIORegister.s

CMakeFiles/peripheral.dir/src/paramRead.o: CMakeFiles/peripheral.dir/flags.make
CMakeFiles/peripheral.dir/src/paramRead.o: ../src/paramRead.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhangjun/code/K100ControlProject/libCreate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/peripheral.dir/src/paramRead.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/peripheral.dir/src/paramRead.o -c /home/zhangjun/code/K100ControlProject/libCreate/src/paramRead.cpp

CMakeFiles/peripheral.dir/src/paramRead.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/peripheral.dir/src/paramRead.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhangjun/code/K100ControlProject/libCreate/src/paramRead.cpp > CMakeFiles/peripheral.dir/src/paramRead.i

CMakeFiles/peripheral.dir/src/paramRead.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/peripheral.dir/src/paramRead.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhangjun/code/K100ControlProject/libCreate/src/paramRead.cpp -o CMakeFiles/peripheral.dir/src/paramRead.s

# Object files for target peripheral
peripheral_OBJECTS = \
"CMakeFiles/peripheral.dir/src/SDR/buffer.o" \
"CMakeFiles/peripheral.dir/src/SDR/context.o" \
"CMakeFiles/peripheral.dir/src/SDR/device.o" \
"CMakeFiles/peripheral.dir/src/SDR/rxstream.o" \
"CMakeFiles/peripheral.dir/src/IIORegister.o" \
"CMakeFiles/peripheral.dir/src/paramRead.o"

# External object files for target peripheral
peripheral_EXTERNAL_OBJECTS =

libperipheral.so: CMakeFiles/peripheral.dir/src/SDR/buffer.o
libperipheral.so: CMakeFiles/peripheral.dir/src/SDR/context.o
libperipheral.so: CMakeFiles/peripheral.dir/src/SDR/device.o
libperipheral.so: CMakeFiles/peripheral.dir/src/SDR/rxstream.o
libperipheral.so: CMakeFiles/peripheral.dir/src/IIORegister.o
libperipheral.so: CMakeFiles/peripheral.dir/src/paramRead.o
libperipheral.so: CMakeFiles/peripheral.dir/build.make
libperipheral.so: CMakeFiles/peripheral.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zhangjun/code/K100ControlProject/libCreate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX shared library libperipheral.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/peripheral.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/peripheral.dir/build: libperipheral.so

.PHONY : CMakeFiles/peripheral.dir/build

CMakeFiles/peripheral.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/peripheral.dir/cmake_clean.cmake
.PHONY : CMakeFiles/peripheral.dir/clean

CMakeFiles/peripheral.dir/depend:
	cd /home/zhangjun/code/K100ControlProject/libCreate/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhangjun/code/K100ControlProject/libCreate /home/zhangjun/code/K100ControlProject/libCreate /home/zhangjun/code/K100ControlProject/libCreate/build /home/zhangjun/code/K100ControlProject/libCreate/build /home/zhangjun/code/K100ControlProject/libCreate/build/CMakeFiles/peripheral.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/peripheral.dir/depend

