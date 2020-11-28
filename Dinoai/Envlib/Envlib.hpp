#ifndef ENVLIB_H
#define ENVLIB_H

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

private:
    Display *_display;
};

#endif
