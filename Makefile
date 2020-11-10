# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/user/Desktop/coolServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/Desktop/coolServer

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/user/Desktop/coolServer/CMakeFiles /home/user/Desktop/coolServer/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/user/Desktop/coolServer/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named coolServer

# Build rule for target.
coolServer: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 coolServer
.PHONY : coolServer

# fast build rule for target.
coolServer/fast:
	$(MAKE) -f CMakeFiles/coolServer.dir/build.make CMakeFiles/coolServer.dir/build
.PHONY : coolServer/fast

handler.o: handler.c.o

.PHONY : handler.o

# target to build an object file
handler.c.o:
	$(MAKE) -f CMakeFiles/coolServer.dir/build.make CMakeFiles/coolServer.dir/handler.c.o
.PHONY : handler.c.o

handler.i: handler.c.i

.PHONY : handler.i

# target to preprocess a source file
handler.c.i:
	$(MAKE) -f CMakeFiles/coolServer.dir/build.make CMakeFiles/coolServer.dir/handler.c.i
.PHONY : handler.c.i

handler.s: handler.c.s

.PHONY : handler.s

# target to generate assembly for a file
handler.c.s:
	$(MAKE) -f CMakeFiles/coolServer.dir/build.make CMakeFiles/coolServer.dir/handler.c.s
.PHONY : handler.c.s

main.o: main.c.o

.PHONY : main.o

# target to build an object file
main.c.o:
	$(MAKE) -f CMakeFiles/coolServer.dir/build.make CMakeFiles/coolServer.dir/main.c.o
.PHONY : main.c.o

main.i: main.c.i

.PHONY : main.i

# target to preprocess a source file
main.c.i:
	$(MAKE) -f CMakeFiles/coolServer.dir/build.make CMakeFiles/coolServer.dir/main.c.i
.PHONY : main.c.i

main.s: main.c.s

.PHONY : main.s

# target to generate assembly for a file
main.c.s:
	$(MAKE) -f CMakeFiles/coolServer.dir/build.make CMakeFiles/coolServer.dir/main.c.s
.PHONY : main.c.s

pong_game.o: pong_game.c.o

.PHONY : pong_game.o

# target to build an object file
pong_game.c.o:
	$(MAKE) -f CMakeFiles/coolServer.dir/build.make CMakeFiles/coolServer.dir/pong_game.c.o
.PHONY : pong_game.c.o

pong_game.i: pong_game.c.i

.PHONY : pong_game.i

# target to preprocess a source file
pong_game.c.i:
	$(MAKE) -f CMakeFiles/coolServer.dir/build.make CMakeFiles/coolServer.dir/pong_game.c.i
.PHONY : pong_game.c.i

pong_game.s: pong_game.c.s

.PHONY : pong_game.s

# target to generate assembly for a file
pong_game.c.s:
	$(MAKE) -f CMakeFiles/coolServer.dir/build.make CMakeFiles/coolServer.dir/pong_game.c.s
.PHONY : pong_game.c.s

server.o: server.c.o

.PHONY : server.o

# target to build an object file
server.c.o:
	$(MAKE) -f CMakeFiles/coolServer.dir/build.make CMakeFiles/coolServer.dir/server.c.o
.PHONY : server.c.o

server.i: server.c.i

.PHONY : server.i

# target to preprocess a source file
server.c.i:
	$(MAKE) -f CMakeFiles/coolServer.dir/build.make CMakeFiles/coolServer.dir/server.c.i
.PHONY : server.c.i

server.s: server.c.s

.PHONY : server.s

# target to generate assembly for a file
server.c.s:
	$(MAKE) -f CMakeFiles/coolServer.dir/build.make CMakeFiles/coolServer.dir/server.c.s
.PHONY : server.c.s

utils.o: utils.c.o

.PHONY : utils.o

# target to build an object file
utils.c.o:
	$(MAKE) -f CMakeFiles/coolServer.dir/build.make CMakeFiles/coolServer.dir/utils.c.o
.PHONY : utils.c.o

utils.i: utils.c.i

.PHONY : utils.i

# target to preprocess a source file
utils.c.i:
	$(MAKE) -f CMakeFiles/coolServer.dir/build.make CMakeFiles/coolServer.dir/utils.c.i
.PHONY : utils.c.i

utils.s: utils.c.s

.PHONY : utils.s

# target to generate assembly for a file
utils.c.s:
	$(MAKE) -f CMakeFiles/coolServer.dir/build.make CMakeFiles/coolServer.dir/utils.c.s
.PHONY : utils.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... coolServer"
	@echo "... handler.o"
	@echo "... handler.i"
	@echo "... handler.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... pong_game.o"
	@echo "... pong_game.i"
	@echo "... pong_game.s"
	@echo "... server.o"
	@echo "... server.i"
	@echo "... server.s"
	@echo "... utils.o"
	@echo "... utils.i"
	@echo "... utils.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

