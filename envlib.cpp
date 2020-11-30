#include "envlib.h"
#include "inputlib.h"
#include <iostream>

using namespace envlib;
using namespace inputlib;
using namespace std;

void envlib::envlib(){
    cout << "Hello from envlib" << endl;
}

envlib::dinoInterface::dinoInterface(int dispId){
    printf("---------------- %d constructor ---------------\n", dispId);

    char displayName[10];
    sprintf(displayName, ":%d", dispId);
    _display = XOpenDisplay(displayName);

    Window rootWindow = XDefaultRootWindow(_display);

    if (_display == nullptr)
    {
        fprintf(stderr, "Cannot open display %s\n", displayName);
        exit(1);
    }

    if (_window == BadWindow)
    {
        fprintf(stderr, "Cannot open root window\n");
        exit(1);
    }

    Window rootReturn, parentReturn;
    Window *children;
    unsigned int nChildren;

    XQueryTree(_display, rootWindow, &rootReturn, &parentReturn, &children, &nChildren);

    if (children[3] == BadWindow)
    {
        fprintf(stderr, "Cannot open Chrome window\n");
        exit(1);
    }

    _window = children[3];

    initWindow(_display, _window);
}

envlib::dinoInterface::dinoInterface(const dinoInterface &old){
    _display = old._display;
}

envlib::dinoInterface::~dinoInterface(){
    // close connection to x display
    XCloseDisplay(_display);
}

int envlib::dinoInterface::getScore(uint32_t &score){
    getScreenshot(_display, _window, _img);

    score = 10; // temp arbitrary value

    return 0; // success
}

int envlib::dinoInterface::getObservation(uint32_t *obs[13]){
    for (int i = 0; i < OBS_SIZE; ++i)
        *obs[i] = i; // temp arbitrary value

    return 0; // success
}

int envlib::dinoInterface::setAction(dinoInterface::Action action){
    switch(action){
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

int envlib::dinoInterface::saveScreenshot(char *filename){
    return writeImage2csv(_img, WIDTH, HEIGHT, filename);
}
