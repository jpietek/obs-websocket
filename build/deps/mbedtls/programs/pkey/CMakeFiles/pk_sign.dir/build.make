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
include deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/depend.make

# Include the progress variables for this target.
include deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/progress.make

# Include the compile flags for this target's objects.
include deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/flags.make

deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign.c.o: deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/flags.make
deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign.c.o: ../deps/mbedtls/programs/pkey/pk_sign.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jp/git/obs-websocket/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign.c.o"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/programs/pkey && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pk_sign.dir/pk_sign.c.o   -c /home/jp/git/obs-websocket/deps/mbedtls/programs/pkey/pk_sign.c

deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pk_sign.dir/pk_sign.c.i"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/programs/pkey && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jp/git/obs-websocket/deps/mbedtls/programs/pkey/pk_sign.c > CMakeFiles/pk_sign.dir/pk_sign.c.i

deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pk_sign.dir/pk_sign.c.s"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/programs/pkey && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jp/git/obs-websocket/deps/mbedtls/programs/pkey/pk_sign.c -o CMakeFiles/pk_sign.dir/pk_sign.c.s

deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign.c.o.requires:

.PHONY : deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign.c.o.requires

deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign.c.o.provides: deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign.c.o.requires
	$(MAKE) -f deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/build.make deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign.c.o.provides.build
.PHONY : deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign.c.o.provides

deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign.c.o.provides.build: deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign.c.o


deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign_automoc.cpp.o: deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/flags.make
deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign_automoc.cpp.o: deps/mbedtls/programs/pkey/pk_sign_automoc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jp/git/obs-websocket/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign_automoc.cpp.o"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/programs/pkey && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pk_sign.dir/pk_sign_automoc.cpp.o -c /home/jp/git/obs-websocket/build/deps/mbedtls/programs/pkey/pk_sign_automoc.cpp

deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign_automoc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pk_sign.dir/pk_sign_automoc.cpp.i"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/programs/pkey && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jp/git/obs-websocket/build/deps/mbedtls/programs/pkey/pk_sign_automoc.cpp > CMakeFiles/pk_sign.dir/pk_sign_automoc.cpp.i

deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign_automoc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pk_sign.dir/pk_sign_automoc.cpp.s"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/programs/pkey && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jp/git/obs-websocket/build/deps/mbedtls/programs/pkey/pk_sign_automoc.cpp -o CMakeFiles/pk_sign.dir/pk_sign_automoc.cpp.s

deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign_automoc.cpp.o.requires:

.PHONY : deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign_automoc.cpp.o.requires

deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign_automoc.cpp.o.provides: deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign_automoc.cpp.o.requires
	$(MAKE) -f deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/build.make deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign_automoc.cpp.o.provides.build
.PHONY : deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign_automoc.cpp.o.provides

deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign_automoc.cpp.o.provides.build: deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign_automoc.cpp.o


# Object files for target pk_sign
pk_sign_OBJECTS = \
"CMakeFiles/pk_sign.dir/pk_sign.c.o" \
"CMakeFiles/pk_sign.dir/pk_sign_automoc.cpp.o"

# External object files for target pk_sign
pk_sign_EXTERNAL_OBJECTS =

deps/mbedtls/programs/pkey/pk_sign: deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign.c.o
deps/mbedtls/programs/pkey/pk_sign: deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign_automoc.cpp.o
deps/mbedtls/programs/pkey/pk_sign: deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/build.make
deps/mbedtls/programs/pkey/pk_sign: deps/mbedtls/library/libmbedtls.a
deps/mbedtls/programs/pkey/pk_sign: deps/mbedtls/library/libmbedx509.a
deps/mbedtls/programs/pkey/pk_sign: deps/mbedtls/library/libmbedcrypto.a
deps/mbedtls/programs/pkey/pk_sign: deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jp/git/obs-websocket/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable pk_sign"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/programs/pkey && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pk_sign.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/build: deps/mbedtls/programs/pkey/pk_sign

.PHONY : deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/build

deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/requires: deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign.c.o.requires
deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/requires: deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/pk_sign_automoc.cpp.o.requires

.PHONY : deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/requires

deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/clean:
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/programs/pkey && $(CMAKE_COMMAND) -P CMakeFiles/pk_sign.dir/cmake_clean.cmake
.PHONY : deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/clean

deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/depend:
	cd /home/jp/git/obs-websocket/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jp/git/obs-websocket /home/jp/git/obs-websocket/deps/mbedtls/programs/pkey /home/jp/git/obs-websocket/build /home/jp/git/obs-websocket/build/deps/mbedtls/programs/pkey /home/jp/git/obs-websocket/build/deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : deps/mbedtls/programs/pkey/CMakeFiles/pk_sign.dir/depend

