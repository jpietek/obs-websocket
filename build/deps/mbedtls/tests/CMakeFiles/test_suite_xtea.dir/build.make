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
include deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/depend.make

# Include the progress variables for this target.
include deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/progress.make

# Include the compile flags for this target's objects.
include deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/flags.make

deps/mbedtls/tests/test_suite_xtea.c: ../deps/mbedtls/tests/scripts/generate_code.pl
deps/mbedtls/tests/test_suite_xtea.c: deps/mbedtls/library/libmbedtls.a
deps/mbedtls/tests/test_suite_xtea.c: ../deps/mbedtls/tests/suites/helpers.function
deps/mbedtls/tests/test_suite_xtea.c: ../deps/mbedtls/tests/suites/main_test.function
deps/mbedtls/tests/test_suite_xtea.c: ../deps/mbedtls/tests/suites/test_suite_xtea.function
deps/mbedtls/tests/test_suite_xtea.c: ../deps/mbedtls/tests/suites/test_suite_xtea.data
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/jp/git/obs-websocket/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating test_suite_xtea.c"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/tests && /usr/bin/perl /home/jp/git/obs-websocket/deps/mbedtls/tests/scripts/generate_code.pl /home/jp/git/obs-websocket/deps/mbedtls/tests/suites test_suite_xtea test_suite_xtea

deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea.c.o: deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/flags.make
deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea.c.o: deps/mbedtls/tests/test_suite_xtea.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jp/git/obs-websocket/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea.c.o"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_suite_xtea.dir/test_suite_xtea.c.o   -c /home/jp/git/obs-websocket/build/deps/mbedtls/tests/test_suite_xtea.c

deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_suite_xtea.dir/test_suite_xtea.c.i"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jp/git/obs-websocket/build/deps/mbedtls/tests/test_suite_xtea.c > CMakeFiles/test_suite_xtea.dir/test_suite_xtea.c.i

deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_suite_xtea.dir/test_suite_xtea.c.s"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jp/git/obs-websocket/build/deps/mbedtls/tests/test_suite_xtea.c -o CMakeFiles/test_suite_xtea.dir/test_suite_xtea.c.s

deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea.c.o.requires:

.PHONY : deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea.c.o.requires

deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea.c.o.provides: deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea.c.o.requires
	$(MAKE) -f deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/build.make deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea.c.o.provides.build
.PHONY : deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea.c.o.provides

deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea.c.o.provides.build: deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea.c.o


deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea_automoc.cpp.o: deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/flags.make
deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea_automoc.cpp.o: deps/mbedtls/tests/test_suite_xtea_automoc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jp/git/obs-websocket/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea_automoc.cpp.o"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/tests && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_suite_xtea.dir/test_suite_xtea_automoc.cpp.o -c /home/jp/git/obs-websocket/build/deps/mbedtls/tests/test_suite_xtea_automoc.cpp

deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea_automoc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_suite_xtea.dir/test_suite_xtea_automoc.cpp.i"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jp/git/obs-websocket/build/deps/mbedtls/tests/test_suite_xtea_automoc.cpp > CMakeFiles/test_suite_xtea.dir/test_suite_xtea_automoc.cpp.i

deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea_automoc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_suite_xtea.dir/test_suite_xtea_automoc.cpp.s"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jp/git/obs-websocket/build/deps/mbedtls/tests/test_suite_xtea_automoc.cpp -o CMakeFiles/test_suite_xtea.dir/test_suite_xtea_automoc.cpp.s

deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea_automoc.cpp.o.requires:

.PHONY : deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea_automoc.cpp.o.requires

deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea_automoc.cpp.o.provides: deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea_automoc.cpp.o.requires
	$(MAKE) -f deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/build.make deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea_automoc.cpp.o.provides.build
.PHONY : deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea_automoc.cpp.o.provides

deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea_automoc.cpp.o.provides.build: deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea_automoc.cpp.o


# Object files for target test_suite_xtea
test_suite_xtea_OBJECTS = \
"CMakeFiles/test_suite_xtea.dir/test_suite_xtea.c.o" \
"CMakeFiles/test_suite_xtea.dir/test_suite_xtea_automoc.cpp.o"

# External object files for target test_suite_xtea
test_suite_xtea_EXTERNAL_OBJECTS =

deps/mbedtls/tests/test_suite_xtea: deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea.c.o
deps/mbedtls/tests/test_suite_xtea: deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea_automoc.cpp.o
deps/mbedtls/tests/test_suite_xtea: deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/build.make
deps/mbedtls/tests/test_suite_xtea: deps/mbedtls/library/libmbedtls.a
deps/mbedtls/tests/test_suite_xtea: deps/mbedtls/library/libmbedx509.a
deps/mbedtls/tests/test_suite_xtea: deps/mbedtls/library/libmbedcrypto.a
deps/mbedtls/tests/test_suite_xtea: deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jp/git/obs-websocket/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable test_suite_xtea"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_suite_xtea.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/build: deps/mbedtls/tests/test_suite_xtea

.PHONY : deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/build

deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/requires: deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea.c.o.requires
deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/requires: deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/test_suite_xtea_automoc.cpp.o.requires

.PHONY : deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/requires

deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/clean:
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/tests && $(CMAKE_COMMAND) -P CMakeFiles/test_suite_xtea.dir/cmake_clean.cmake
.PHONY : deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/clean

deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/depend: deps/mbedtls/tests/test_suite_xtea.c
	cd /home/jp/git/obs-websocket/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jp/git/obs-websocket /home/jp/git/obs-websocket/deps/mbedtls/tests /home/jp/git/obs-websocket/build /home/jp/git/obs-websocket/build/deps/mbedtls/tests /home/jp/git/obs-websocket/build/deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : deps/mbedtls/tests/CMakeFiles/test_suite_xtea.dir/depend

