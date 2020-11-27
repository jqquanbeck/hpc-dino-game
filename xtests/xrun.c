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

#define MAX_INSTANCES 50

#define WIDTH 600
#define HEIGHT 150

#define FPS 60

void writeXImage2csv(XImage *, char *);
void typeString(Display *, char *);
void tapKey(Display *, KeySym);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Provide the number of instances followed by the first display indentifier.\n");
        exit(1);
    }
    
    int N = atoi(argv[1]);
    int firstDisplay = atoi(argv[2]);
    

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
            exit(1);
        }
    }
    printf("Established connections to displays\n");

    printf("Navigating to chrome://dino\n");
    for (int i = 0; i < N; ++i)
    {
        Window window = XDefaultRootWindow(display[i]);

        Window root, parent;
        Window *children;
        int nChildren;

        XQueryTree(display[i], window, &root, &parent, &children, &nChildren);

        XMoveResizeWindow(display[i], children[3], 0, 0, 600, 150);

        // Navigate to chrome://dino
        typeString(display[i], "chrome://dino");
        tapKey(display[i], XK_KP_Enter);

        // Go fullscreen with F11
        tapKey(display[i], XK_F11);
    }

    usleep(5000000);

    for (int i = 0; i < N; ++i)
    {
        // Trigger start of game
        XTestFakeMotionEvent(display[i], XDefaultScreen(display[i]), 50, 50, CurrentTime);
        XTestFakeButtonEvent(display[i], 1, True, CurrentTime);
        XFlush(display[i]);
        XTestFakeButtonEvent(display[i], 1, False, CurrentTime);
        XFlush(display[i]);
    }

    // main loop
    printf("Entering main loop\n");

    clock_t start, end;
    double executionTime;
    while (1)
    {
        start = clock();

        for (int i = 0; i < N; ++i)
        {
            tapKey(display[i], XK_Up);
        }

        // maintain 60 fps
        end = clock();
        executionTime = ((double) (end - start)) / CLOCKS_PER_SEC;

        uint sleepTime = (1.0/FPS - executionTime)*1000000;
        usleep(sleepTime);
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
    XTestFakeKeyEvent(display, sym, 1, 0);
    XFlush(display);
    usleep(10000);
    XTestFakeKeyEvent(display, sym, 0, 0);
    XFlush(display);
}

