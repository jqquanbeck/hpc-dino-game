#ifndef INPUTLIB_H
#define INPUTLIB_H

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>

#define MAX_INSTANCES 50

#define WIDTH 600
#define HEIGHT 150

namespace inputlib{

    // externally called
    int initWindow(Display *display, Window window);
    int getScreenshot(Display *display, Window window, uint8_t *img);

    // internally called
    int image2ByteArray(XImage *xImg, uint8_t *img);
    int writeImage2csv(uint8_t *img, const unsigned int w, const unsigned int h, char *filename);
    void typeString(Display *display, char *str);
    void tapKey(Display *display, KeySym key);
    void pressKey(Display *display, KeySym key);
    void releaseKey(Display *display, KeySym key);
    
}

#endif
