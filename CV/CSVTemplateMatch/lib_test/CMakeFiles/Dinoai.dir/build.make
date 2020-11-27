# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /gpfs/shared/apps_local/cmake/3.18.0/bin/cmake

# The command to remove a file.
RM = /gpfs/shared/apps_local/cmake/3.18.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alhanshaw/Project/hpc-dino-game/CV/CSVTemplateMatch/lib_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alhanshaw/Project/hpc-dino-game/CV/CSVTemplateMatch/lib_test

# Include any dependencies generated for this target.
include CMakeFiles/Dinoai.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Dinoai.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Dinoai.dir/flags.make

CMakeFiles/Dinoai.dir/Dinoai.cpp.o: CMakeFiles/Dinoai.dir/flags.make
CMakeFiles/Dinoai.dir/Dinoai.cpp.o: Dinoai.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alhanshaw/Project/hpc-dino-game/CV/CSVTemplateMatch/lib_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Dinoai.dir/Dinoai.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Dinoai.dir/Dinoai.cpp.o -c /home/alhanshaw/Project/hpc-dino-game/CV/CSVTemplateMatch/lib_test/Dinoai.cpp

CMakeFiles/Dinoai.dir/Dinoai.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Dinoai.dir/Dinoai.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alhanshaw/Project/hpc-dino-game/CV/CSVTemplateMatch/lib_test/Dinoai.cpp > CMakeFiles/Dinoai.dir/Dinoai.cpp.i

CMakeFiles/Dinoai.dir/Dinoai.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Dinoai.dir/Dinoai.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alhanshaw/Project/hpc-dino-game/CV/CSVTemplateMatch/lib_test/Dinoai.cpp -o CMakeFiles/Dinoai.dir/Dinoai.cpp.s

# Object files for target Dinoai
Dinoai_OBJECTS = \
"CMakeFiles/Dinoai.dir/Dinoai.cpp.o"

# External object files for target Dinoai
Dinoai_EXTERNAL_OBJECTS =

Dinoai: CMakeFiles/Dinoai.dir/Dinoai.cpp.o
Dinoai: CMakeFiles/Dinoai.dir/build.make
Dinoai: Matchlib/libMatchlib.a
Dinoai: /home/alhanshaw/OpenCV/build/lib/libopencv_dnn.so.4.5.0
Dinoai: /home/alhanshaw/OpenCV/build/lib/libopencv_gapi.so.4.5.0
Dinoai: /home/alhanshaw/OpenCV/build/lib/libopencv_highgui.so.4.5.0
Dinoai: /home/alhanshaw/OpenCV/build/lib/libopencv_ml.so.4.5.0
Dinoai: /home/alhanshaw/OpenCV/build/lib/libopencv_objdetect.so.4.5.0
Dinoai: /home/alhanshaw/OpenCV/build/lib/libopencv_photo.so.4.5.0
Dinoai: /home/alhanshaw/OpenCV/build/lib/libopencv_stitching.so.4.5.0
Dinoai: /home/alhanshaw/OpenCV/build/lib/libopencv_video.so.4.5.0
Dinoai: /home/alhanshaw/OpenCV/build/lib/libopencv_calib3d.so.4.5.0
Dinoai: /home/alhanshaw/OpenCV/build/lib/libopencv_features2d.so.4.5.0
Dinoai: /home/alhanshaw/OpenCV/build/lib/libopencv_flann.so.4.5.0
Dinoai: /home/alhanshaw/OpenCV/build/lib/libopencv_videoio.so.4.5.0
Dinoai: /home/alhanshaw/OpenCV/build/lib/libopencv_imgcodecs.so.4.5.0
Dinoai: /home/alhanshaw/OpenCV/build/lib/libopencv_imgproc.so.4.5.0
Dinoai: /home/alhanshaw/OpenCV/build/lib/libopencv_core.so.4.5.0
Dinoai: CMakeFiles/Dinoai.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alhanshaw/Project/hpc-dino-game/CV/CSVTemplateMatch/lib_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Dinoai"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Dinoai.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Dinoai.dir/build: Dinoai

.PHONY : CMakeFiles/Dinoai.dir/build

CMakeFiles/Dinoai.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Dinoai.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Dinoai.dir/clean

CMakeFiles/Dinoai.dir/depend:
	cd /home/alhanshaw/Project/hpc-dino-game/CV/CSVTemplateMatch/lib_test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alhanshaw/Project/hpc-dino-game/CV/CSVTemplateMatch/lib_test /home/alhanshaw/Project/hpc-dino-game/CV/CSVTemplateMatch/lib_test /home/alhanshaw/Project/hpc-dino-game/CV/CSVTemplateMatch/lib_test /home/alhanshaw/Project/hpc-dino-game/CV/CSVTemplateMatch/lib_test /home/alhanshaw/Project/hpc-dino-game/CV/CSVTemplateMatch/lib_test/CMakeFiles/Dinoai.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Dinoai.dir/depend

