#ifndef ENVLIB_H
#define ENVLIB_H

#include "Inputlib.hpp"
#include <stdint.h>

#include <X11/Xlib.h>

#define OBS_SIZE 13

class Envlib
{
public:
    Envlib(int dispId);
    Envlib(const Envlib &old);
    ~Envlib();

    enum Action { NONE, UP, DOWN };

    int getScore(uint32_t &score);
    int getObservation(uint32_t *obs[OBS_SIZE]);
    int setAction(Envlib::Action action);

    // for testing only
    int saveScreenshot(char *filename);

private:
    Display *_display;
    Window _window;
    uint8_t _img[HEIGHT][WIDTH];
};

#endif
