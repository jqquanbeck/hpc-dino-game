#!/bin/bash

# Define build tools
CC = g++
CFLAGS = -Wall -fPIC
LINKER = $(CC) -o
COMPILER = $(CC) $(CFLAGS) -c
STATIC_LIB = ar rcs
SHARED_LIB = $(CC) -shared -o

# OpenCV build options and linker targets/locations
OPENCV_LINKER_OPTIONS = -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_stitching
OPENCV_LIBRARY_LOCATIONS = -L/usr/local/lib/
OPENCV_INCLUDE_LOCATIONS = `pkg-config --cflags --libs opencv4`

# X11 build options and linker targets/locations
X11_LINKER_OPTIONS = -lX11 -lstdc++ -lXtst
X11_LIBRARY_LOCATIONS = -L/usr/X11/lib
X11_INCLUDE_LOCATIONS = -I/usr/local/include

# Aggregated build options and linker targets/locations
AGG_LINKER_OPTIONS = $(X11_LINKER_OPTIONS) $(OPENCV_LINKER_OPTIONS)
AGG_LIBRARY_LOCATIONS = $(X11_LIBRARY_LOCATIONS) $(OPENCV_LIBRARY_LOCATIONS)
AGG_INCLUDE_LOCATIONS = $(X11_INCLUDE_LOCATIONS) $(OPENCV_INCLUDE_LOCATIONS)


# Link object files together and produce main executable
# dinoai: dinoai.o matchlib.o inputlib.o
# 	$(LINKER) dinoai $(AGG_INCLUDE_LOCATIONS) $(AGG_LIBRARY_LOCATIONS)  dinoai.o matchlib.o inputlib.o $(AGG_LINKER_OPTIONS)

# # Compile objects
# dinoai.o: dinoai.cpp
# 	$(COMPILER) dinoai.cpp

dinolib.so: matchlib.o inputlib.o envlib.o
	$(SHARED_LIB) dinolib.so $(AGG_INCLUDE_LOCATIONS) $(AGG_LIBRARY_LOCATIONS) matchlib.o inputlib.o envlib.o $(AGG_LINKER_OPTIONS)
matchlib.o: matchlib.cpp
	$(COMPILER) $(OPENCV_INCLUDE_LOCATIONS) $(OPENCV_LIBRARY_LOCATIONS) matchlib.cpp $(OPENCV_LINKER_OPTIONS)
inputlib.o: inputlib.cpp
	$(COMPILER) $(X11_INCLUDE_LOCATIONS) $(X11_LIBRARY_LOCATIONS) inputlib.cpp $(X11_LINKER_OPTIONS)
envlib.o: envlib.cpp
	$(COMPILER) $(X11_INCLUDE_LOCATIONS) $(X11_LIBRARY_LOCATIONS) envlib.cpp $(X11_LINKER_OPTIONS)

# Remove residuals
clean:
	rm -f *.o *.a *.so dinoai