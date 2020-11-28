#include "Envlib.hpp"

#include "Inputlib.hpp"

Envlib::Envlib(int dispId)
{
    printf("---------------- %d constructor ---------------\n", dispId);

     char displayName[10];
    sprintf(displayName, ":%d", dispId);
    _display = XOpenDisplay(displayName);
    _window = XDefaultRootWindow(_display);

    if (_display == NULL)
    {
        fprintf(stderr, "Cannot open display %s\n", displayName);
        exit(1);
    }

    initWindow(_display, _window);
}

Envlib::Envlib(const Envlib &old)
{
    _display = old._display;
}

Envlib::~Envlib()
{
    // close connection to x display
    XCloseDisplay(_display);
}

int Envlib::getScore(uint32_t &score)
{
    getScreenshot(_display, _window, _img);

    score = 10; // temp arbitrary value

    return 0; // success
}

int Envlib::getObservation(uint32_t *obs[13])
{
    for (int i = 0; i < OBS_SIZE; ++i)
        *obs[i] = i; // temp arbitrary value

    return 0; // success
}

int Envlib::setAction(Envlib::Action action)
{
    switch(action)
    {
        case NONE:
            releaseKey(_display, XK_Up);
            releaseKey(_display, XK_Down);
            break;
        
        case UP:
            releaseKey(_display, XK_Down);
            pressKey(_display, XK_Up);
            break;

        case DOWN:
            releaseKey(_display, XK_Up);
            pressKey(_display, XK_Down);
            break;
    }

    return 0; // success
}

int Envlib::saveScreenshot(char *filename)
{
    return writeImage2csv(_img, WIDTH, HEIGHT, filename);
}
