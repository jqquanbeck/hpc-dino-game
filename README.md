# DinoAI - Computer-vision based neural network training

## Description
Dinoai is a neural network that is trained from the information provided only by image processing and nothing else. Usually, most neural networks are trained using data provided by internal variables that are pulled directly from the application's code itself. Dinoai is able to train itself purely from the data provided by the graphical output of the computer itself.

An eventual goal of the project is to apply the computer vision to video provided by camera input instead of direct input from the X Window System.

## Project Organization
The cmake project was created using visual studio 2019 though the default cmake project. If interested, one is able to open the folder though Visual Studio 2019 and access a slew of streamlined tools such as automated copy and building to the server, syntax highlighting of cmake, automated cpp header importing, and many other features. While these features are nice, they are not required at all, and the project can be just as easily manipulated with any text editor such as vscode.

The project directory `Dinoai` contains the main entrypoint `Dinoai.cpp` and the two libraries `Inputlib` and `Matchlib` where `Inputlib` is a library for accessing bitmap information of the game though `LibX11` and `Matchlib` is a library for image matching functions utlizing `OpenCV`.

## Build
### Cmake Installation
Dinoai uses Cmake to provide automatic makefile generation. If cmake is not installed on your system, for Windows, install you system's specific installation from https://cmake.org/download/. If you are on linux instead, using your preferred package manager of choice, install `cmake`.

Apt Package Manager:
```bash
$ sudo apt-get install cmake
```

### Dependency installation
Unfortunately, the design of Cmake leaves dependencies to the user, and the dependent libraries must be installed individually . This being said, the cmake script is designed to find the library's details automagically; this makes installation somewhat easier as the script will find the installed libraries no matter the system; if the script cannot find the library in question, you can supply the library's path using the command line.

The project currently uses `OpenCV` and `LibX11` where both are avaialbe on unix systems. X11 is technically avaiable on windows, although it seems to be proprietary code. One note to be made about `OpenCV` dependencies is that there exist "hidden" dependencies that are not installed when OpenCV is installed. The hidden dependencies were as follows: `glew`, `libqt5widgets5`, and `hdf5`.

### Cmake Usage
Cmake will generate a makefile with the first invocation of cmake, and the second invocation will run the generated makefile and output to `"./build"`.
``` bash
$ git clone "https://github.com/jqquanbeck/hpc-dino-game.git" # Clone code
$ cd hpc-dino-game                                            # Move into directory
$ cmake --parallel -S "." -B "./build"                        # Generate Makefile
$ cmake --build  "./build" --verbose --parallel               # Execute Makefile
```