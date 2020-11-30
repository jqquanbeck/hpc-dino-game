#!/bin/bash

# Define build tools
CC = g++
CFLAGS = -std=c++11 -Wall -fPIC
LINKER = $(CC) $(CFLAGS) -o
COMPILER = $(CC) $(CFLAGS) -c
STATIC_LIB = ar rcs
SHARED_LIB = $(CC) -shared -o

# OpenCV build options and linker targets/locations
OPENCV_LINKER_OPTIONS = -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_stitching
OPENCV_LIBRARY_LOCATIONS = -L/usr/local/lib/
OPENCV_INCLUDE_LOCATIONS = -I/usr/local/include/opencv -I/usr/local/include/opencv2

# X11 build options and linker targets/locations
X11_LINKER_OPTIONS = -lX11 -lstdc++ -lXtst
X11_LIBRARY_LOCATIONS = -L/usr/X11/lib
X11_INCLUDE_LOCATIONS = -I/usr/local/include

# OpenMP build options and linker targets/locations
OPENMP_LINKER_OPTIONS = -fopenmp
OPENMP_LIBRARY_LOCATIONS =
OPENMP_INCLUDE_LOCATIONS =

# Aggregated build options and linker targets/locations
AGG_LINKER_OPTIONS = $(X11_LINKER_OPTIONS) $(OPENCV_LINKER_OPTIONS) $(OPENMP_LINKER_OPTIONS)
AGG_LIBRARY_LOCATIONS = $(X11_LIBRARY_LOCATIONS) $(OPENCV_LIBRARY_LOCATIONS) $(OPENMP_LIBRARY_LOCATIONS)
AGG_INCLUDE_LOCATIONS = $(X11_INCLUDE_LOCATIONS) $(OPENCV_INCLUDE_LOCATIONS) $(OPENMP_INCLUDE_LOCATIONS)


# Link object files together and produce main executable
# dinoai: dinoai.o matchlib.o inputlib.o
#   $(LINKER) dinoai $(AGG_INCLUDE_LOCATIONS) $(AGG_LIBRARY_LOCATIONS)  dinoai.o matchlib.o inputlib.o $(AGG_LINKER_OPTIONS)

# # Compile objects
# dinoai.o: dinoai.cpp
# 	$(COMPILER) dinoai.cpp

dinolib.so: matchlib.o inputlib.o envlib.o pyhandler.o
	$(SHARED_LIB) dinolib.so $(AGG_INCLUDE_LOCATIONS) $(AGG_LIBRARY_LOCATIONS) envlib.o matchlib.o inputlib.o pyhandler.o $(AGG_LINKER_OPTIONS)
matchlib.o: matchlib.cpp
	$(COMPILER) matchlib.cpp
inputlib.o: inputlib.cpp
	$(COMPILER) inputlib.cpp
envlib.o: envlib.cpp
	$(COMPILER) envlib.cpp
pyhandler.o: pyhandler.cpp envlib.o
	$(COMPILER) pyhandler.cpp

# Remove residuals
clean:
	rm -f *.o *.a *.so *.pyc dinoai