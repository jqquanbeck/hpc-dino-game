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

int initWindows(int N, int firstDisplay)
{
    // Connect to X display
    printf("Connecting to x displays\n");
    Display *display[MAX_INSTANCES];
    for (int i = 0; i < N; ++i)
    {
        char displayName[10];
        sprintf(displayName, ":%d", firstDisplay + i);
        display[i] = XOpenDisplay(displayName);

        if (display[i] == NULL)
        {
            fprintf(stderr, "Cannot open display %s\n", displayName);
            return 1;
        }
    }

    printf("Navigating to chrome://dino\n");
    for (int i = 0; i < N; ++i)
    {
        Window window = XDefaultRootWindow(display[i]);

        Window root, parent;
        Window *children;
        unsigned int nChildren;

        XQueryTree(display[i], window, &root, &parent, &children, &nChildren);

        XMoveResizeWindow(display[i], children[3], 0, 0, 600, 150);

        // Navigate to chrome://dino
        typeString(display[i], (char*)("chrome://dino"));
        tapKey(display[i], XK_KP_Enter);

        // Go fullscreen with F11
        tapKey(display[i], XK_F11);
    }

    usleep(5000000);

    // Trigger start of game
    for (int i = 0; i < N; ++i)
    {
        // Click mouse
        XTestFakeMotionEvent(display[i], XDefaultScreen(display[i]), 50, 50, CurrentTime);
        XTestFakeButtonEvent(display[i], 1, True, CurrentTime);
        XFlush(display[i]);
        XTestFakeButtonEvent(display[i], 1, False, CurrentTime);
        XFlush(display[i]);

        // Hit up arrow key
        tapKey(display[i], XK_Up);
        XFlush(display[i]);
    }

    // Disconnect from X
    for (int i = 0; i < N; ++i)
        XCloseDisplay(display[i]);

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
