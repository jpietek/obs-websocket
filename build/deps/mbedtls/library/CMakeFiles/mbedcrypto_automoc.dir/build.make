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

# Utility rule file for mbedcrypto_automoc.

# Include the progress variables for this target.
include deps/mbedtls/library/CMakeFiles/mbedcrypto_automoc.dir/progress.make

deps/mbedtls/library/CMakeFiles/mbedcrypto_automoc:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/jp/git/obs-websocket/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic moc and uic for target mbedcrypto"
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/library && /usr/bin/cmake -E cmake_autogen /home/jp/git/obs-websocket/build/deps/mbedtls/library/CMakeFiles/mbedcrypto_automoc.dir/ ""

mbedcrypto_automoc: deps/mbedtls/library/CMakeFiles/mbedcrypto_automoc
mbedcrypto_automoc: deps/mbedtls/library/CMakeFiles/mbedcrypto_automoc.dir/build.make

.PHONY : mbedcrypto_automoc

# Rule to build all files generated by this target.
deps/mbedtls/library/CMakeFiles/mbedcrypto_automoc.dir/build: mbedcrypto_automoc

.PHONY : deps/mbedtls/library/CMakeFiles/mbedcrypto_automoc.dir/build

deps/mbedtls/library/CMakeFiles/mbedcrypto_automoc.dir/clean:
	cd /home/jp/git/obs-websocket/build/deps/mbedtls/library && $(CMAKE_COMMAND) -P CMakeFiles/mbedcrypto_automoc.dir/cmake_clean.cmake
.PHONY : deps/mbedtls/library/CMakeFiles/mbedcrypto_automoc.dir/clean

deps/mbedtls/library/CMakeFiles/mbedcrypto_automoc.dir/depend:
	cd /home/jp/git/obs-websocket/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jp/git/obs-websocket /home/jp/git/obs-websocket/deps/mbedtls/library /home/jp/git/obs-websocket/build /home/jp/git/obs-websocket/build/deps/mbedtls/library /home/jp/git/obs-websocket/build/deps/mbedtls/library/CMakeFiles/mbedcrypto_automoc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : deps/mbedtls/library/CMakeFiles/mbedcrypto_automoc.dir/depend

