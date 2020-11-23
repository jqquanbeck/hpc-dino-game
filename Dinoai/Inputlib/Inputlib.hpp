#ifndef INPUTLIB_H
#define INPUTLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>

#include <unistd.h>

void writeXImage2csv(XImage *img, char *filename);
void typeString(Display *display, char *str);
void tapKey(Display *display, KeySym key);

#endif