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
include deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/depend.make

# Include the progress variables for this target.
include deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/progress.make

# Include the compile flags for this target's objects.
include deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/flags.make

deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server.c.o: deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/flags.make
deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server.c.o: ../deps/mbedtls/programs/ssl/dtls_server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jp/git/obs-websocket/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server.c.o"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/programs/ssl && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/dtls_server.dir/dtls_server.c.o   -c /home/jp/git/obs-websocket/deps/mbedtls/programs/ssl/dtls_server.c

deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dtls_server.dir/dtls_server.c.i"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/programs/ssl && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jp/git/obs-websocket/deps/mbedtls/programs/ssl/dtls_server.c > CMakeFiles/dtls_server.dir/dtls_server.c.i

deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dtls_server.dir/dtls_server.c.s"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/programs/ssl && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jp/git/obs-websocket/deps/mbedtls/programs/ssl/dtls_server.c -o CMakeFiles/dtls_server.dir/dtls_server.c.s

deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server.c.o.requires:

.PHONY : deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server.c.o.requires

deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server.c.o.provides: deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server.c.o.requires
	$(MAKE) -f deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/build.make deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server.c.o.provides.build
.PHONY : deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server.c.o.provides

deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server.c.o.provides.build: deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server.c.o


deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server_automoc.cpp.o: deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/flags.make
deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server_automoc.cpp.o: deps/mbedtls/programs/ssl/dtls_server_automoc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jp/git/obs-websocket/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server_automoc.cpp.o"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/programs/ssl && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/dtls_server.dir/dtls_server_automoc.cpp.o -c /home/jp/git/obs-websocket/build/deps/mbedtls/programs/ssl/dtls_server_automoc.cpp

deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server_automoc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dtls_server.dir/dtls_server_automoc.cpp.i"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/programs/ssl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jp/git/obs-websocket/build/deps/mbedtls/programs/ssl/dtls_server_automoc.cpp > CMakeFiles/dtls_server.dir/dtls_server_automoc.cpp.i

deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server_automoc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dtls_server.dir/dtls_server_automoc.cpp.s"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/programs/ssl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jp/git/obs-websocket/build/deps/mbedtls/programs/ssl/dtls_server_automoc.cpp -o CMakeFiles/dtls_server.dir/dtls_server_automoc.cpp.s

deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server_automoc.cpp.o.requires:

.PHONY : deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server_automoc.cpp.o.requires

deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server_automoc.cpp.o.provides: deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server_automoc.cpp.o.requires
	$(MAKE) -f deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/build.make deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server_automoc.cpp.o.provides.build
.PHONY : deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server_automoc.cpp.o.provides

deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server_automoc.cpp.o.provides.build: deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server_automoc.cpp.o


# Object files for target dtls_server
dtls_server_OBJECTS = \
"CMakeFiles/dtls_server.dir/dtls_server.c.o" \
"CMakeFiles/dtls_server.dir/dtls_server_automoc.cpp.o"

# External object files for target dtls_server
dtls_server_EXTERNAL_OBJECTS =

deps/mbedtls/programs/ssl/dtls_server: deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server.c.o
deps/mbedtls/programs/ssl/dtls_server: deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server_automoc.cpp.o
deps/mbedtls/programs/ssl/dtls_server: deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/build.make
deps/mbedtls/programs/ssl/dtls_server: deps/mbedtls/library/libmbedtls.a
deps/mbedtls/programs/ssl/dtls_server: deps/mbedtls/library/libmbedx509.a
deps/mbedtls/programs/ssl/dtls_server: deps/mbedtls/library/libmbedcrypto.a
deps/mbedtls/programs/ssl/dtls_server: deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jp/git/obs-websocket/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable dtls_server"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/programs/ssl && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dtls_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/build: deps/mbedtls/programs/ssl/dtls_server

.PHONY : deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/build

deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/requires: deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server.c.o.requires
deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/requires: deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/dtls_server_automoc.cpp.o.requires

.PHONY : deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/requires

deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/clean:
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/programs/ssl && $(CMAKE_COMMAND) -P CMakeFiles/dtls_server.dir/cmake_clean.cmake
.PHONY : deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/clean

deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/depend:
	cd /home/jp/git/obs-websocket/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jp/git/obs-websocket /home/jp/git/obs-websocket/deps/mbedtls/programs/ssl /home/jp/git/obs-websocket/build /home/jp/git/obs-websocket/build/deps/mbedtls/programs/ssl /home/jp/git/obs-websocket/build/deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : deps/mbedtls/programs/ssl/CMakeFiles/dtls_server.dir/depend

