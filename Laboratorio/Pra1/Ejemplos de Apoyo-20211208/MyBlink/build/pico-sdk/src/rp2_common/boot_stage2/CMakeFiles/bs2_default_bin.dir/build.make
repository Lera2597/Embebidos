# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = C:\RPPicoSDK\cmake\bin\cmake.exe

# The command to remove a file.
RM = C:\RPPicoSDK\cmake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\Dropbox\udea\Embebidos\Laboratorio\Pra1\Ejemplos de Apoyo-20211208\MyBlink"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\Dropbox\udea\Embebidos\Laboratorio\Pra1\Ejemplos de Apoyo-20211208\MyBlink\build"

# Utility rule file for bs2_default_bin.

# Include any custom commands dependencies for this target.
include pico-sdk/src/rp2_common/boot_stage2/CMakeFiles/bs2_default_bin.dir/compiler_depend.make

# Include the progress variables for this target.
include pico-sdk/src/rp2_common/boot_stage2/CMakeFiles/bs2_default_bin.dir/progress.make

pico-sdk/src/rp2_common/boot_stage2/CMakeFiles/bs2_default_bin: pico-sdk/src/rp2_common/boot_stage2/bs2_default.bin

pico-sdk/src/rp2_common/boot_stage2/bs2_default.bin: pico-sdk/src/rp2_common/boot_stage2/bs2_default.elf
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="D:\Dropbox\udea\Embebidos\Laboratorio\Pra1\Ejemplos de Apoyo-20211208\MyBlink\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Generating bs2_default.bin"
	cd /d D:\Dropbox\udea\Embebidos\Laboratorio\Pra1\EJEMPL~1\MyBlink\build\pico-sdk\src\RP2_CO~1\BOOT_S~1 && "C:\RPPicoSDK\armcc\10 2021.10\bin\arm-none-eabi-objcopy.exe" -Obinary "D:/Dropbox/udea/Embebidos/Laboratorio/Pra1/Ejemplos de Apoyo-20211208/MyBlink/build/pico-sdk/src/rp2_common/boot_stage2/bs2_default.elf" "D:/Dropbox/udea/Embebidos/Laboratorio/Pra1/Ejemplos de Apoyo-20211208/MyBlink/build/pico-sdk/src/rp2_common/boot_stage2/bs2_default.bin"

bs2_default_bin: pico-sdk/src/rp2_common/boot_stage2/CMakeFiles/bs2_default_bin
bs2_default_bin: pico-sdk/src/rp2_common/boot_stage2/bs2_default.bin
bs2_default_bin: pico-sdk/src/rp2_common/boot_stage2/CMakeFiles/bs2_default_bin.dir/build.make
.PHONY : bs2_default_bin

# Rule to build all files generated by this target.
pico-sdk/src/rp2_common/boot_stage2/CMakeFiles/bs2_default_bin.dir/build: bs2_default_bin
.PHONY : pico-sdk/src/rp2_common/boot_stage2/CMakeFiles/bs2_default_bin.dir/build

pico-sdk/src/rp2_common/boot_stage2/CMakeFiles/bs2_default_bin.dir/clean:
	cd /d D:\Dropbox\udea\Embebidos\Laboratorio\Pra1\EJEMPL~1\MyBlink\build\pico-sdk\src\RP2_CO~1\BOOT_S~1 && $(CMAKE_COMMAND) -P CMakeFiles\bs2_default_bin.dir\cmake_clean.cmake
.PHONY : pico-sdk/src/rp2_common/boot_stage2/CMakeFiles/bs2_default_bin.dir/clean

pico-sdk/src/rp2_common/boot_stage2/CMakeFiles/bs2_default_bin.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\Dropbox\udea\Embebidos\Laboratorio\Pra1\Ejemplos de Apoyo-20211208\MyBlink" C:\RPPicoSDK\sdk\pico\pico-sdk\src\rp2_common\boot_stage2 "D:\Dropbox\udea\Embebidos\Laboratorio\Pra1\Ejemplos de Apoyo-20211208\MyBlink\build" "D:\Dropbox\udea\Embebidos\Laboratorio\Pra1\Ejemplos de Apoyo-20211208\MyBlink\build\pico-sdk\src\rp2_common\boot_stage2" "D:\Dropbox\udea\Embebidos\Laboratorio\Pra1\Ejemplos de Apoyo-20211208\MyBlink\build\pico-sdk\src\rp2_common\boot_stage2\CMakeFiles\bs2_default_bin.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : pico-sdk/src/rp2_common/boot_stage2/CMakeFiles/bs2_default_bin.dir/depend

