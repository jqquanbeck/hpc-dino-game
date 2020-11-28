#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include <vector>
#include <string>

#include "Envlib.hpp"

using namespace std;

#define WIDTH 600
#define HEIGHT 150

#define FPS 60

//int MatchMain();
int InputlibMain(int, int);

int main(int argc, char *argv[])
{
	// Process arguments
	if (argc != 3)
    {
        printf("Provide the number of instances followed by the first display indentifier.\n");
        exit(1);
    }
    
    int N = atoi(argv[1]);
    int firstDisplay = atoi(argv[2]);

	printf("\n\n==================== Starting DinoAI ====================\n");
	printf("Batch size = %d\n\n", N);

	InputlibMain(N, firstDisplay);
    //MatchMain();
}

/*int MatchMain()
{
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
}*/

int InputlibMain(int N, int firstDisplay)
{
	std::vector<Envlib> environments;

	environments.reserve(N);

    for (int i = 0; i < N; ++i)
	{
		environments.emplace_back(firstDisplay + i);
	}
	
	printf("\nInitialization complete\n");

    // main loop
    printf("Entering main loop\n");

    clock_t start, end;
    double executionTime;
    while (1)
    {
        start = clock();

        for (int i = 0; i < N; ++i)
        {
            environments[i].setAction(Envlib::UP);
			usleep(1000);
			environments[i].setAction(Envlib::NONE);
        }

        // maintain 60 fps
        end = clock();
        executionTime = ((double) (end - start)) / CLOCKS_PER_SEC;

        uint sleepTime = (1.0/FPS - executionTime)*1000000;
        usleep(sleepTime);
    }

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
