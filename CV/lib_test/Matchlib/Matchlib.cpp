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

bool isNight(Mat Img)
{
	//Samples are (413,25), (422, 22), and (407,20)
	//These lie between the H and I, in the crook of the I, and in the crook of the H, respectively
	int coords[][2] = { {413, 25}, {422, 22}, {407, 20} };
	int avg = 0;
	int numPoints = (int)( sizeof(coords) / sizeof(coords[0]) );
	
	for (int i = 0; i < numPoints; i++) {
		avg += (int)Img.at<uchar>( coords[i][1], coords[i][0] );
	}
	avg = avg/numPoints;
	
	if(avg <= 128) {
		return true;
	}
	else {
		return false;
	}
}

int getScore(Mat Img) { //Takes an unaltered image (e.g. not cropped) and determines the score
	//some things to implement: automatically switching between night and day (easy fix)
	//this will load the num_X.png images every time this function is called, which is super inefficient
		//Find some way to save that loading
		//probably just open the numbers once in main and pass them into the function each time?
	
	int score = 0;
	int coords[][2] = {{547,20}, {536,20}, {525,20}, {514,20}, {503,20} }; //locations of the TOP LEFT corner of each score digit
	Mat numImg[10]; //array of mats to hold the template numbers
	Mat scoreImg[5] = Mat(11, 9, CV_8UC1); //array of mats to hold the captured scores from the screenshot
	
	string numImgLoc = "../../dinosprite/fullsize/regular/num_";
	
	//read number images into array of Mats;
	for(int i = 0; i <= 9; i++) {
		string numImgFullPath = numImgLoc + to_string(i) + ".png";
		numImg[i] = imread(numImgFullPath, IMREAD_GRAYSCALE);
	}
	
	//prepare image for template matching
	cout << "size of digit: " << sizeof(scoreImg) << endl;
	for(int digit = 0; digit < sizeof(scoreImg)/sizeof(scoreImg[0]); digit++) { //for each digit
		scoreImg[digit] = Img( Rect( coords[digit][0], coords[digit][1], 9, 11) ); //crop the image
		imwrite("output/scoreImg(" + to_string(digit) + ").png" , scoreImg[digit]); //write each score image to PNG for debug
	}
	
	
	/*
	for (int digit = 0; digit <= 4; digit++) { //for each coord
		for(int num = 0; num <= 9; num++) { //do for i from 0 to 9
			
		}
	}
	*/
	return score;
}

Mat CSVtoMat(int rows, int cols, string filepath) { 
	//this function sucks because it doesn't automatically determine size of CSV
	//find some way to make the mat automatically the size of the CSV without much overhead.
	
	Mat CSVImg;
	CSVImg = Mat(rows, cols, CV_8UC1); //Create rows x cols pixel Mat made of uint8s
	ifstream myfile(filepath); //open csv file
	
	string CSVstr; //temp to hold a line from the csv file
	
	if(myfile) { //if file is valid
		for (int i=0; i<CSVImg.rows-1; i++) { //for each row
			for (int j=0; j<CSVImg.cols-1; j++) { //for each column
				getline(myfile, CSVstr, ','); //get a line from the CSV up to the next comma
				CSVImg.at<uchar>(i,j) = stoi(CSVstr); //save the data from the CSV into an int
			}
		}
	}
	
	return CSVImg;
}		
