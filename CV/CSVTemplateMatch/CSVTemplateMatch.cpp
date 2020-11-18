#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <omp.h>
#include <stdio.h>

using namespace std;
using namespace cv;

vector<Point> TemplateMatch(Mat srcImg, Mat templImg, float tolerance) {
	vector<Point> matchLocations;
	Point tempLoc;
	Mat result; //mat object to store the result of the template match algo	
	int result_rows = srcImg.rows - templImg.rows + 1; //calculate result image rows
	int result_cols = srcImg.cols - templImg.cols + 1; //calculate result image cols

	result = Mat(result_rows, result_cols, CV_32FC1); //create mat to hold result of template match CV_8UC1
  
	matchTemplate(srcImg, templImg, result, TM_CCOEFF_NORMED); //perform template matching	TM_SQDIFF_NORMED

	normalize(result, result, 0.0, 1.0, NORM_MINMAX); //normalize the result NORM_MINMAX
	
	cout.precision(5);
	//cout << "Result size: " << result.rows << "," << result.cols << "(rows,cols)" << endl;
	
	double minVal; double maxVal; Point minLoc; Point maxLoc; //localize the best match with minMaxLoc
	minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
	
	//Note: Though x is the column variable, and y is the row variable, openCV Mats are in the form of (y,x)
	for (int x = 0; x < result.cols; x++) {
		for (int y = 0; y < result.rows; y++) {
			if(result.at<float>(y,x) >= tolerance) {
				//cout << x+templImg.cols/2 << "," << y+templImg.rows/2 << ": " << result.at<float>(y,x) << endl;
				tempLoc.x = x+templImg.cols/2;
				tempLoc.y = y+templImg.rows/2;
				matchLocations.push_back(tempLoc);
			}
		}
	}
	
	return matchLocations;
}

int main() {
	Mat CSVImg, templateImg; //Create two Mat objects, one for the source image, one for the template
	Point matchPt; //Point object to hold match location
	vector<Point> matchPts;
	CSVImg = Mat(150, 600, CV_8UC1); //Create 150x600px mat made of uint8
	string CSVstr; //Temp string to hold line from csv file
	ofstream logfile("log.txt", ios::trunc); //log file name, truncated as to rewrite the log file each time the code is run
	
	for (int k = 0; k < 355; k++) {
		
		string filePath = "../Screenshots_Joel/"; //path string
		string fileName = "img_" + to_string(k) + ".csv"; //create filename string
		string fullFileName = filePath+fileName;
		
		ifstream myfile(fullFileName); //open csv
		
		if(myfile) { //if file is valid
			for (int i=0; i<CSVImg.rows-1; i++) { //for each rows
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
	return EXIT_SUCCESS;
}