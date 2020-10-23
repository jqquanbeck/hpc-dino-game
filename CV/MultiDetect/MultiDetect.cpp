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

void writeToCSV(Mat src, string filename ) {
	filename+=".csv";
	ofstream myFile(filename);
	for(int i = 0; i < src.rows; i++) {
		for(int j = 0; j < src.cols; j++) {
			myFile<<(int)src.at<uchar>(i,j) << ",";
		}
		myFile<<"\n";
	}
	myFile.close();
	return;
}

Point MatchingMethod(Mat srcImg, Mat templImg) {
	
	Point matchLoc;
	Mat result;
	Mat threshMat;
	
	int result_cols =  srcImg.cols - templImg.cols + 1;
	int result_rows = srcImg.rows - templImg.rows + 1;

	result.create(result_rows, result_cols, CV_8UC1);
	
  
	matchTemplate(srcImg, templImg, result, TM_SQDIFF_NORMED);
	
	writeToCSV(result, "resultaftermatch");
	
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat() ); //-1 in the 6th arguement means return the same type as given
	writeToCSV(result, "resultnormalized");
	
	
	int nummatches = 1;
	for (int i = 0; i < result.rows; i++ )
	{
		for (int j = 0; j < result.cols; j++ )
		{
			if ((double)result.at<uchar>(i,j) < 1)
			{
				cout << "Number of matches: " << nummatches << " Location: " << i << "," << j;
				printf("value: %4f \n", (double)result.at<uchar>(i,j));
				nummatches++;
			}
		}
	}

	double minVal; double maxVal; Point minLoc; Point maxLoc; //localize the best match with minMaxLoc
	minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
	matchLoc = minLoc; //for SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
	printf("MatchLoc = %d, %d \n", minLoc.x, minLoc.y); //print location of matched template
	cout << minVal << endl;
	matchLoc.x += templImg.cols/2;
	matchLoc.y += templImg.rows/2;
	return matchLoc;
}

int main() {

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
	writeToCSV(CSVImg, "csvimg");
	matchPt = MatchingMethod(CSVImg, templateImg);
	printf("MatchLoc = %d, %d \n", matchPt.x, matchPt.y); //print location of matched template
	
	
	
	myfile.close(); // close file
	return EXIT_SUCCESS;
}