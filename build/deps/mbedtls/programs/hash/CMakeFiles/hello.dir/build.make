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
CMAKE_SOURCE_DIR = /home/jp/git/obs-websocket

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jp/git/obs-websocket/build

# Include any dependencies generated for this target.
include deps/mbedtls/programs/hash/CMakeFiles/hello.dir/depend.make

# Include the progress variables for this target.
include deps/mbedtls/programs/hash/CMakeFiles/hello.dir/progress.make

# Include the compile flags for this target's objects.
include deps/mbedtls/programs/hash/CMakeFiles/hello.dir/flags.make

deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello.c.o: deps/mbedtls/programs/hash/CMakeFiles/hello.dir/flags.make
deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello.c.o: ../deps/mbedtls/programs/hash/hello.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jp/git/obs-websocket/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello.c.o"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/programs/hash && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hello.dir/hello.c.o   -c /home/jp/git/obs-websocket/deps/mbedtls/programs/hash/hello.c

deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hello.dir/hello.c.i"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/programs/hash && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jp/git/obs-websocket/deps/mbedtls/programs/hash/hello.c > CMakeFiles/hello.dir/hello.c.i

deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hello.dir/hello.c.s"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/programs/hash && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jp/git/obs-websocket/deps/mbedtls/programs/hash/hello.c -o CMakeFiles/hello.dir/hello.c.s

deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello.c.o.requires:

.PHONY : deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello.c.o.requires

deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello.c.o.provides: deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello.c.o.requires
	$(MAKE) -f deps/mbedtls/programs/hash/CMakeFiles/hello.dir/build.make deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello.c.o.provides.build
.PHONY : deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello.c.o.provides

deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello.c.o.provides.build: deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello.c.o


deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello_automoc.cpp.o: deps/mbedtls/programs/hash/CMakeFiles/hello.dir/flags.make
deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello_automoc.cpp.o: deps/mbedtls/programs/hash/hello_automoc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jp/git/obs-websocket/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello_automoc.cpp.o"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/programs/hash && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hello.dir/hello_automoc.cpp.o -c /home/jp/git/obs-websocket/build/deps/mbedtls/programs/hash/hello_automoc.cpp

deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello_automoc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hello.dir/hello_automoc.cpp.i"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/programs/hash && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jp/git/obs-websocket/build/deps/mbedtls/programs/hash/hello_automoc.cpp > CMakeFiles/hello.dir/hello_automoc.cpp.i

deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello_automoc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hello.dir/hello_automoc.cpp.s"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/programs/hash && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jp/git/obs-websocket/build/deps/mbedtls/programs/hash/hello_automoc.cpp -o CMakeFiles/hello.dir/hello_automoc.cpp.s

deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello_automoc.cpp.o.requires:

.PHONY : deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello_automoc.cpp.o.requires

deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello_automoc.cpp.o.provides: deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello_automoc.cpp.o.requires
	$(MAKE) -f deps/mbedtls/programs/hash/CMakeFiles/hello.dir/build.make deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello_automoc.cpp.o.provides.build
.PHONY : deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello_automoc.cpp.o.provides

deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello_automoc.cpp.o.provides.build: deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello_automoc.cpp.o


# Object files for target hello
hello_OBJECTS = \
"CMakeFiles/hello.dir/hello.c.o" \
"CMakeFiles/hello.dir/hello_automoc.cpp.o"

# External object files for target hello
hello_EXTERNAL_OBJECTS =

deps/mbedtls/programs/hash/hello: deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello.c.o
deps/mbedtls/programs/hash/hello: deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello_automoc.cpp.o
deps/mbedtls/programs/hash/hello: deps/mbedtls/programs/hash/CMakeFiles/hello.dir/build.make
deps/mbedtls/programs/hash/hello: deps/mbedtls/library/libmbedtls.a
deps/mbedtls/programs/hash/hello: deps/mbedtls/library/libmbedx509.a
deps/mbedtls/programs/hash/hello: deps/mbedtls/library/libmbedcrypto.a
deps/mbedtls/programs/hash/hello: deps/mbedtls/programs/hash/CMakeFiles/hello.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jp/git/obs-websocket/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable hello"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/programs/hash && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hello.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
deps/mbedtls/programs/hash/CMakeFiles/hello.dir/build: deps/mbedtls/programs/hash/hello

.PHONY : deps/mbedtls/programs/hash/CMakeFiles/hello.dir/build

deps/mbedtls/programs/hash/CMakeFiles/hello.dir/requires: deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello.c.o.requires
deps/mbedtls/programs/hash/CMakeFiles/hello.dir/requires: deps/mbedtls/programs/hash/CMakeFiles/hello.dir/hello_automoc.cpp.o.requires

.PHONY : deps/mbedtls/programs/hash/CMakeFiles/hello.dir/requires

deps/mbedtls/programs/hash/CMakeFiles/hello.dir/clean:
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/programs/hash && $(CMAKE_COMMAND) -P CMakeFiles/hello.dir/cmake_clean.cmake
.PHONY : deps/mbedtls/programs/hash/CMakeFiles/hello.dir/clean

deps/mbedtls/programs/hash/CMakeFiles/hello.dir/depend:
	cd /home/jp/git/obs-websocket/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jp/git/obs-websocket /home/jp/git/obs-websocket/deps/mbedtls/programs/hash /home/jp/git/obs-websocket/build /home/jp/git/obs-websocket/build/deps/mbedtls/programs/hash /home/jp/git/obs-websocket/build/deps/mbedtls/programs/hash/CMakeFiles/hello.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : deps/mbedtls/programs/hash/CMakeFiles/hello.dir/depend

