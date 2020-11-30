#ifndef ENVLIB_H
#define ENVLIB_H

#include <stdint.h>
#include <X11/Xlib.h>

#include "inputlib.h"

#define OBS_SIZE 15 //4 enemies * 3 fields per enemy + 1 for height + 1 for score = 15

namespace envlib{

    // void envlib(int out[3]); // hello world function

    class dinoInterface{
        public:
            dinoInterface(int dispId);
            dinoInterface(const dinoInterface &old);
            ~dinoInterface();

            enum Action { NONE, UP, DOWN };

<<<<<<< HEAD
            int getScore(uint32_t &score);
            int getObservation(uint32_t obs[OBS_SIZE]);
=======
            //int getScore(uint32_t &score);
            int getObservation(uint32_t *obs[OBS_SIZE], uint32_t &score);
>>>>>>> cad741017065991c82e55981d4b9ab41f44ee729
            int setAction(dinoInterface::Action action);

            // for testing only
            int saveScreenshot(char *filename);

        private:
            Display *_display;
            Window _window;
            uint8_t _img[HEIGHT][WIDTH];
    };

}

#endif
