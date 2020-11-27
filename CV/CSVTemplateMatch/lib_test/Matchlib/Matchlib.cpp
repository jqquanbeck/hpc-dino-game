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