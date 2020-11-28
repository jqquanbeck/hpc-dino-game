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
		
	//The way this works is by using a "template" image which contains all digits 0-9 in a row
	//then the cropped image from the given screengrab is used as the actual template of the TM function
	//then where the highest value of the TM result is where the correct number is
	//basically instead of looking for each number within the extracted digit
	//we look for where the extracted digit matches each number
	
	int score = 0;
	int coords[][2] = {{547,20}, {536,20}, {525,20}, {514,20}, {503,20} }; //locations of the TOP LEFT corner of each score digit
	
	//using "smaller" sprite seems to give erroneous results. For such a easy TM, using the smaller sprite doesn't save much time anyway
	string numImgLoc = "../../dinosprite/fullsize/regular/num_all.png"; //read number images into array of Mats;
	
	Mat numImg = imread(numImgLoc, IMREAD_GRAYSCALE);; //array of mats to hold the template numbers
	Mat scoreImg[5] = Mat(11, 9, CV_8UC1); //array of mats to hold the captured scores from the screenshot
	
	Mat result; //mat object to store the result of the template match algo	
	
	//prepare image for template matching
	for(int digit = 0; digit < sizeof(scoreImg)/sizeof(scoreImg[0]); digit++) { //for each digit
		scoreImg[digit] = Img( Rect( coords[digit][0], coords[digit][1], 9, 11) ); //crop the image
		imwrite("output/scoreImg(" + to_string(digit) + ").png" , scoreImg[digit]); //write each score image to PNG for debug
	}
	
	int result_rows = numImg.rows - 11 + 1; //calculate result image rows
	int result_cols = numImg.cols - 9 + 1; //calculate result image cols
	
	for (int digit = 0; digit <= 4; digit++) { //for each digit
		matchTemplate(scoreImg[digit], numImg, result, TM_CCOEFF_NORMED); //perform template matching	TM_SQDIFF_NORMED
		normalize(result, result, 0.0, 1, NORM_MINMAX); //normalize the result NORM_MINMAX
		
		Mat debug_result;
		normalize(result, debug_result, 0.0, 255, NORM_MINMAX); //normalize the result NORM_MINMAX
		
		//Random thought: does the range 0-1 imply that the *BEST* match is 1, or that a *PERFECT* match is a 1?
		//if somehow the input is screwed up and not actually the scoreboard of the game, will there still be a resultant 1?
		
		imwrite("output/resImg(" +to_string(digit) + ")_smaller.png" , debug_result); //write each to png for debug
		//Note: Though x is the column variable, and y is the row variable, openCV Mats are in the form of (y,x)
		float tempScoreLoc;	
		for (int x = 0; x < result.cols; x++) {
			for (int y = 0; y < result.rows; y++) {
				if(result.at<float>(y,x) == 1) {
					//cout << "(" << x << "," << y << ") = " << result.at<float>(y,x) << "\t(Digit = " << digit << ")" << endl;
					tempScoreLoc = x;
				}
			}
		}
		
		//This is the worst code ever. I'm sorry
		int factor;
		if(tempScoreLoc <= 8) {
			factor = 0;
		}
		else if (tempScoreLoc > 8 && tempScoreLoc <= 17)
			factor = 1;
		else if (tempScoreLoc > 17 && tempScoreLoc <= 28)
			factor = 2;
		else if (tempScoreLoc > 28 && tempScoreLoc <= 38)
			factor = 3;
		else if (tempScoreLoc > 38 && tempScoreLoc <= 48)
			factor = 4;
		else if (tempScoreLoc > 48 && tempScoreLoc <= 58)
			factor = 5;
		else if (tempScoreLoc > 58 && tempScoreLoc <= 68)
			factor = 6;
		else if (tempScoreLoc > 68 && tempScoreLoc <= 78)
			factor = 7;
		else if (tempScoreLoc > 78 && tempScoreLoc <= 88)
			factor = 8;
		else
			factor = 9;
		
		score += factor*pow(10,digit);
	}
	

	
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
