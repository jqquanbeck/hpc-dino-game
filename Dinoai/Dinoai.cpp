// KEEP ABOVE LIBX11 HEADERS!!! DO NOT MOVE HEADER!!!
#include <opencv2/opencv.hpp>
// KEEP ABOVE LIBX11 HEADERS!!! DO NOT MOVE HEADER!!!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>

#include <string>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>

#include "Inputlib/Inputlib.hpp"
#include "Matchlib/Matchlib.hpp"

using namespace std;

// #define DISPLAY ":0"

#define WIDTH 600
#define HEIGHT 150

#define FPS 60

int main() {
    printf("Hello World!");
}

int InputlibMain() {
    const char* DISPLAY = getenv("DISPLAY");
    // Connect to X
    Display* display;
    display = XOpenDisplay(DISPLAY);

    if (display == NULL) {
        fprintf(stderr, "Cannot open display %s\n", DISPLAY);
        exit(1);
    }

    // Navigate to chrome://dino
    printf("Entering URL\n");
    char dinopath[14] = "chrome://dino";
    typeString(display, dinopath);
    tapKey(display, XK_KP_Enter);

    // Go fullscreen with F11
    printf("Entering fullscreen mode (F11)\n");
    tapKey(display, XK_F11);
    usleep(5000000);

    // Start the game and git rid of F11 popup
    tapKey(display, XK_Up);

    // Save test screenshot
    Window window = XRootWindow(display, XDefaultScreen(display));
    XImage* img;
    usleep(5000000);
    img = XGetImage(display, window, 0, 0, WIDTH, HEIGHT, AllPlanes, XYPixmap);
    printf("Saving screenshot test.csv\n");
    char csvname[14] = "logs/test.csv";
    writeXImage2csv(img, csvname);

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
        executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;

        uint sleepTime = (1.0 / FPS - executionTime) * 1000000;
        usleep(sleepTime);
    }

    // Disconnect from X
    XCloseDisplay(display);

    return 0;
}

int MatchlibMain() {

    Mat CSVImg, templateImg;
    Point matchPt;
    CSVImg = Mat(150, 600, CV_8UC1);
    string temp;
    ifstream myfile ("test_cacti.csv"); //file to be opened

    if(myfile) { //if file is valid
 	    for (int i=0; i<CSVImg.rows-1; i++) {
 		    for (int j=0; j<CSVImg.cols-1; j++) {
 			    getline(myfile, temp, ',');
 			    CSVImg.at<uchar>(i,j) = stoi(temp);
 		    }
 	    }
    }

    imwrite("csvimg.png", CSVImg);
    templateImg = imread("dino_run1.png", IMREAD_GRAYSCALE );
    matchPt = MatchingMethod(CSVImg, templateImg);
    printf("MatchLoc = %d, %d \n", matchPt.x, matchPt.y); //print location of matched template

    myfile.close(); // close file
    return EXIT_SUCCESS;
}
