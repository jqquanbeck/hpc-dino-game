#ifndef ENVLIB_H
#define ENVLIB_H

#include <stdint.h>
#include <X11/Xlib.h>

#include "inputlib.h"

#define OBS_SIZE 13

namespace envlib{

    void envlib(); // hello world function

    class dinoInterface{
        public:
            dinoInterface(int dispId);
            dinoInterface(const dinoInterface &old);
            ~dinoInterface();

            enum Action { NONE, UP, DOWN };

            int getScore(uint32_t &score);
            int getObservation(uint32_t *obs[OBS_SIZE]);
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