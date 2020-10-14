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

#define DISPLAY ":2"

#define WIDTH 600
#define HEIGHT 150

#define FPS 60

void writeXImage2csv(XImage *, char *);
void typeString(Display *, char *);
void tapKey(Display *, KeySym);

int main()
{
    // Connect to X
    Display *display;
    display = XOpenDisplay(DISPLAY);

    if (display == NULL) {
        fprintf(stderr, "Cannot open display %s\n", DISPLAY);
        exit(1);
    }

    // Navigate to chrome://dino
    printf("Entering URL\n");
    typeString(display, "chrome://dino");
    tapKey(display, XK_KP_Enter);

    // Go fullscreen with F11
    printf("Entering fullscreen mode (F11)\n");
    tapKey(display, XK_F11);
    usleep(5000000);

    // Start the game and git rid of F11 popup
    tapKey(display, XK_Up);

    // Save test screenshot
    Window window = XRootWindow(display, XDefaultScreen(display));
    XImage *img;
    usleep(5000000);
    img = XGetImage(display, window, 0, 0, WIDTH, HEIGHT, AllPlanes, XYPixmap);
    printf("Saving screenshot test.csv\n");
    writeXImage2csv(img, "logs/test.csv");

    printf("Entering main loop\n");
    clock_t start, end;
    double executionTime;

    while (1)
    {
        start = clock();

        tapKey(display, XK_Up);
        img = XGetImage(display, window, 0, 0, WIDTH, HEIGHT, AllPlanes, XYPixmap);

        // maintain 60 fps
        end = clock();
        executionTime = ((double) (end - start)) / CLOCKS_PER_SEC;

        uint sleepTime = (1.0/FPS - executionTime)*1000000;
        usleep(sleepTime);
    }

    // Disconnect from X
    XCloseDisplay(display);

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