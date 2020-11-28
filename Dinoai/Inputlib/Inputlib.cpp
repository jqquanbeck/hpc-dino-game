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

#include "Inputlib.hpp"

int initWindow(Display *display)
{
    printf("Navigating to chrome://dino\n");
    Window window = XDefaultRootWindow(display);

    Window root, parent;
    Window *children;
    unsigned int nChildren;

    XQueryTree(display, window, &root, &parent, &children, &nChildren);

    XMoveResizeWindow(display, children[3], 0, 0, 600, 150);

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
    printf("Hitting up arrow\n");
    tapKey(display, XK_Up);
    printf("Flushing display?\n");
    XFlush(display);
    printf("Failing to return...\n");

    return 0;
}

void writeXImage2csv(XImage *img, char *filename)
{
    FILE *fh = fopen(filename,"w+");

    for(int y = 0; y < img->height; y++)
    {
        for(int x = 0; x < img->width - 1; x++)
        {
            fprintf(fh, "%d,", (uint8_t)(XGetPixel(img, x, y) & img->blue_mask));
        }

        fprintf(fh, "%d\n", (uint8_t)(XGetPixel(img, img->width - 1, y) & img->blue_mask));
    }

    fclose(fh);
}

void typeString(Display *display, char *str)
{
    KeySym sym;
    for (int i = 0; str[i] != '\0'; ++i)
    {
        tapKey(display, str[i]);
    }
}

void tapKey(Display *display, KeySym key)
{
    KeyCode sym = XKeysymToKeycode(display, key);

    // Simulate the keypress
    XTestFakeKeyEvent(display, sym, 1, 0); // press
    XFlush(display);
    usleep(10000);
    XTestFakeKeyEvent(display, sym, 0, 0); // release
    XFlush(display);
}

void pressKey(Display *display, KeySym key)
{
    KeyCode sym = XKeysymToKeycode(display, key);

    // Simulate the keypress
    XTestFakeKeyEvent(display, sym, 1, 0); // press
    XFlush(display);
}

void releaseKey(Display *display, KeySym key)
{
    KeyCode sym = XKeysymToKeycode(display, key);

    // Simulate the keypress
    XTestFakeKeyEvent(display, sym, 0, 0); // release
    XFlush(display);
}
