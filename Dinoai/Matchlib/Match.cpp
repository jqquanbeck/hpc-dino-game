#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/imgproc.hpp"
#include <omp.h>
#include <stdio.h>
#include "Matchlib.hpp"

using namespace std;
using namespace cv;


int main() {
	Mat CSVImg, templateImg; //Create two Mat objects, one for the source image, one for the template
	Point matchPt; //Point object to hold match location
	vector<Point> matchPts;
	CSVImg = Mat(150, 600, CV_8UC1); //Create 150x600px mat made of uint8
	string CSVstr; //Temp string to hold line from csv file
	ofstream logfile("log.txt", ios::trunc); //log file name, truncated as to rewrite the log file each time the code is run
	
	
	//string file = "../Screenshots_Joel/inverted.csv";
	string file = "../Screenshots_Joel/img_10.csv";

	ifstream myfile(file); //open csv

	if(myfile) { //if file is valid
		for (int i=0; i<CSVImg.rows-1; i++) { //for each row
			for (int j=0; j<CSVImg.cols-1; j++) { //for each column
				getline(myfile, CSVstr, ','); //get a line from the CSV up to the next comma
				CSVImg.at<uchar>(i,j) = stoi(CSVstr); //save the data from the CSV into an int
			}
		}
	}
	
	bool nightState = isNight(CSVImg);
	cout << "nightState: " << nightState << endl;
	
	
	for (int k = 0; k < 355; k++) {
		
		string filePath = "../Screenshots_Joel/"; //path string
		string fileName = "img_" + to_string(k) + ".csv"; //create filename string
		string fullFileName = filePath+fileName;
		
		ifstream myfile(fullFileName); //open csv
		
		if(myfile) { //if file is valid
			for (int i=0; i<CSVImg.rows-1; i++) { //for each row
				for (int j=0; j<CSVImg.cols-1; j++) { //for each column
					getline(myfile, CSVstr, ','); //get a line from the CSV up to the next comma
					CSVImg.at<uchar>(i,j) = stoi(CSVstr); //save the data from the CSV into an int
				}
			}
		}
		else { //throw simple error if file isn't found
			cout << "ERROR in reading file!" << endl;	
		}
		
		if(k == 0) {//if statement to only write one png
			imwrite("output/csvimg.png", CSVImg); //write the original image to PNG for debug
		}
		
		string templFileloc;
		if(nightState == false) {
			templFileLoc = "../../dinosprite/regular/";
		}
		else {
			templFileLoc = "../../dinosprite/inverted/";
		}
			
		templateImg = imread("templatePNG/dino_template.png", IMREAD_GRAYSCALE); //read the template image as a grayscale image
		
		matchPts = TemplateMatch(CSVImg, templateImg, 0.99); //match the read CSV image to the template
		
		logfile << "File path: " << filePath << endl;
		for (int j = 0; j < matchPts.size(); j++) { //for all of the matched points
			//printf("(%d, %d)\t", matchPts[i].x, matchPts[i].y);
			logfile << fileName << ": ";
			logfile << "(" <<  matchPts[j].x << "," << matchPts[j].y << ")   ";
		}
		logfile << "\n"; 
		
		myfile.close(); //Close file
	}
	
	logfile.close();
	*/
	return EXIT_SUCCESS;
}