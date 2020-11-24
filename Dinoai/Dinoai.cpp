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
    MatchMain();
}

int MatchMain() {
	Mat CSVImg, templateImg; //Create two Mat objects, one for the source image, one for the template
	Point matchPt; //Point object to hold match location
	vector<Point> matchPts;
	CSVImg = Mat(150, 600, CV_8UC1); //Create 150x600px mat made of uint8
	string CSVstr; //Temp string to hold line from csv file
	ofstream logfile("log.txt", ios::trunc); //log file name, truncated as to rewrite the log file each time the code is run


	//string file = "../Screenshots_Joel/inverted.csv";
	string file = "../Screenshots_Joel/img_10.csv";

	ifstream myfile(file); //open csv

	if (myfile) { //if file is valid
		for (int i = 0; i < CSVImg.rows - 1; i++) { //for each row
			for (int j = 0; j < CSVImg.cols - 1; j++) { //for each column
				getline(myfile, CSVstr, ','); //get a line from the CSV up to the next comma
				CSVImg.at<uchar>(i, j) = stoi(CSVstr); //save the data from the CSV into an int
			}
		}
	}

	bool nightState = isNight(CSVImg);
	cout << "nightState: " << nightState << endl;


	for (int k = 0; k < 355; k++) {

		string filePath = "../Screenshots_Joel/"; //path string
		string fileName = "img_" + to_string(k) + ".csv"; //create filename string
		string fullFileName = filePath + fileName;

		ifstream myfile(fullFileName); //open csv

		if (myfile) { //if file is valid
			for (int i = 0; i < CSVImg.rows - 1; i++) { //for each row
				for (int j = 0; j < CSVImg.cols - 1; j++) { //for each column
					getline(myfile, CSVstr, ','); //get a line from the CSV up to the next comma
					CSVImg.at<uchar>(i, j) = stoi(CSVstr); //save the data from the CSV into an int
				}
			}
		}
		else { //throw simple error if file isn't found
			cout << "ERROR in reading file!" << endl;
		}

		if (k == 0) {//if statement to only write one png
			imwrite("output/csvimg.png", CSVImg); //write the original image to PNG for debug
		}

		string templFileloc = "../../dinosprite/regular/";
		if (nightState == true) {
			templFileloc = "../../dinosprite/inverted/";
		}

		templateImg = imread("templatePNG/dino_template.png", IMREAD_GRAYSCALE); //read the template image as a grayscale image

		matchPts = TemplateMatch(CSVImg, templateImg, 0.99); //match the read CSV image to the template

		logfile << "File path: " << filePath << endl;
		for (int j = 0; j < matchPts.size(); j++) { //for all of the matched points
			//printf("(%d, %d)\t", matchPts[i].x, matchPts[i].y);
			logfile << fileName << ": ";
			logfile << "(" << matchPts[j].x << "," << matchPts[j].y << ")   ";
		}
		logfile << "\n";

		myfile.close(); //Close file
	}

	logfile.close();

	return EXIT_SUCCESS;
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

//int MatchlibMain() {
//
//    Mat CSVImg, templateImg;
//    Point matchPt;
//    CSVImg = Mat(150, 600, CV_8UC1);
//    string temp;
//    ifstream myfile ("test_cacti.csv"); //file to be opened
//
//    if(myfile) { //if file is valid
// 	    for (int i=0; i<CSVImg.rows-1; i++) {
// 		    for (int j=0; j<CSVImg.cols-1; j++) {
// 			    getline(myfile, temp, ',');
// 			    CSVImg.at<uchar>(i,j) = stoi(temp);
// 		    }
// 	    }
//    }
//
//    imwrite("csvimg.png", CSVImg);
//    templateImg = imread("dino_run1.png", IMREAD_GRAYSCALE );
//    matchPt = TemplateMatch(CSVImg, templateImg, /*ERROR-FIXME*/);
//    printf("MatchLoc = %d, %d \n", matchPt.x, matchPt.y); //print location of matched template
//
//    myfile.close(); // close file
//    return EXIT_SUCCESS;
//}
