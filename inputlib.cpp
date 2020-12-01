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

#include "inputlib.h"

using namespace std;

int inputlib::initWindow(Display *display, Window window){
    printf("Navigating to chrome://dino\n");

    XMoveResizeWindow(display, window, 0, 0, 600, 150);

    // Navigate to chrome://dino
    typeString(display, (char*)("chrome://dino"));
    tapKey(display, XK_KP_Enter);

    // Go fullscreen with F11
    printf("Entering fullscreen mode\n");
    tapKey(display, XK_F11);

    usleep(1000000);

    // Trigger start of game
    // Click mouse
    printf("Starting game\n");
    XTestFakeMotionEvent(display, XDefaultScreen(display), 50, 50, CurrentTime);
    XTestFakeButtonEvent(display, 1, True, CurrentTime);
    XFlush(display);
    XTestFakeButtonEvent(display, 1, False, CurrentTime);
    XFlush(display);

    // Hit up arrow key
    tapKey(display, XK_Up);
    XFlush(display);

    return 0;
}

int inputlib::getScreenshot(Display *display, Window window, uint8_t *img){
    //XImage *xImg;
    //xImg = XGetImage(display, window, 0, 0, WIDTH, HEIGHT, AllPlanes, XYPixmap);

    //image2ByteArray(xImg, img);

    return 0;
}

int inputlib::image2ByteArray(XImage *xImg, uint8_t *img){
    for(int y = 0; y < xImg->height; y++)
        for(int x = 0; x < xImg->width; x++)
             *(img + y*WIDTH + x) = (uint8_t)(XGetPixel(xImg, x, y) & xImg->blue_mask);

    return 0; // success
}

int inputlib::writeImage2csv(uint8_t *img, const unsigned int w, const unsigned int h, char *filename){
    FILE *fh = fopen(filename,"w+");

    if (fh == NULL)
    {
        printf("Failed to open file %s\n", filename);
        return 1;
    }

    for(unsigned int y = 0; y < h; y++)
    {
        for(unsigned int x = 0; x < w - 1; x++)
        {
            fprintf(fh, "%d,",  *(img + y*WIDTH + x));
        }

        fprintf(fh, "%d\n",  *(img + y*WIDTH + w-1));
    }

    fclose(fh);

    return 0; // success
}

void inputlib::typeString(Display *display, char *str){
    for (int i = 0; str[i] != '\0'; ++i)
    {
        tapKey(display, str[i]);
    }
}

void inputlib::tapKey(Display *display, KeySym key){
    KeyCode sym = XKeysymToKeycode(display, key);

    // Simulate the keypress
    XTestFakeKeyEvent(display, sym, 1, 0); // press
    XFlush(display);
    usleep(10000);
    XTestFakeKeyEvent(display, sym, 0, 0); // release
    XFlush(display);
}

void inputlib::pressKey(Display *display, KeySym key){
    KeyCode sym = XKeysymToKeycode(display, key);

    // Simulate the keypress
    XTestFakeKeyEvent(display, sym, 1, 0); // press
    XFlush(display);
}

void inputlib::releaseKey(Display *display, KeySym key){
    KeyCode sym = XKeysymToKeycode(display, key);

    // Simulate the keypress
    XTestFakeKeyEvent(display, sym, 0, 0); // release
    XFlush(display);
}
