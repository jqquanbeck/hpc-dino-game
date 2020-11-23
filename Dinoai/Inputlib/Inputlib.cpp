#include "Inputlib.hpp"

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
        sym = XKeysymToKeycode(display, str[i]);

        // Simulate the keypress
        XTestFakeKeyEvent(display, sym, 1, 0);
        XTestFakeKeyEvent(display, sym, 0, 0);
        XFlush(display);
    }
}

void tapKey(Display *display, KeySym key)
{
    KeySym sym = XKeysymToKeycode(display, key);

    // Simulate the keypress
    XTestFakeKeyEvent(display, sym, 1, 0);
    XTestFakeKeyEvent(display, sym, 0, 0);
    XFlush(display);
}
