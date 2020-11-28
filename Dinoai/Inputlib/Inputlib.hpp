#ifndef INPUTLIB_H
#define INPUTLIB_H

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

#define FPS 60

// externally called
int initWindow(Display *display);

// internally called
void writeXImage2csv(XImage *img, char *filename);
void typeString(Display *display, char *str);
void tapKey(Display *display, KeySym key);
void pressKey(Display *display, KeySym key);
void releaseKey(Display *display, KeySym key);

#endif