# DinoAI - Computer-vision based neural network training

## Description
Dinoai is a neural network that is trained from the information provided only by image processing and nothing else. Usually, most neural networks are trained using data provided by internal variables that are pulled directly from the application's code itself. Dinoai is able to train itself purely from the data provided by the graphical output of the computer itself.

An eventual goal of the project is to apply the computer vision to video provided by camera input instead of direct input from the X Window System.

## Project Organization
The cmake project was created using visual studio 2019 though the default cmake project. If interested, one is able to open the folder though Visual Studio 2019 and access a slew of streamlined tools such as automated copy and building to the server, syntax highlighting of cmake, automated cpp header importing, and many other features. While these features are nice, they are not required at all, and the project can be just as easily manipulated with any text editor such as vscode.

The project directory `Dinoai` contains the main entrypoint `Dinoai.cpp` and the two libraries `Inputlib` and `Matchlib` where `Inputlib` is a library for accessing bitmap information of the game though `LibX11` and `Matchlib` is a library for image matching functions utlizing `OpenCV`.

## Build

### Installation and building
Installation is simple, but limited to building on the IRIS server on the SDSU campus cluster.

First, several modules have to be loaded to build and execute the code. The code relies on several specific packages available on the IRIS cluster. This process is necessary each time you log on the cluster.
``` bash
$ module load spack libx11 python/3.7 tensorflow/1.11.0-gpu 
```

Alternatively, one can save the current collection of packages with `module save` to the default user profile and then restore them using `module restore`
``` bash
$ module save
$ module restore
```

The project can then be cloned onto the server and then built using make.
``` bash
$ git clone "https://github.com/jqquanbeck/hpc-dino-game.git" # Clone code
$ cd hpc-dino-game                                            # Move into directory
$ make                                                        # Make the project
```

### Running the code

The project can be run using the provided batching tool `./tools/run.sh` from the project's root folder to run an array of instances for training.
``` bash
$ ./tools/run.sh
```