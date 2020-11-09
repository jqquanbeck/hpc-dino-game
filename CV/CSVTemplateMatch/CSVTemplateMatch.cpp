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

Point TemplateMatch(Mat srcImg, Mat templImg) {
	
	Mat result; //mat object to store the result of the template match algo	
	int result_rows = srcImg.rows - templImg.rows + 1; //calculate result image rows
	int result_cols = srcImg.cols - templImg.cols + 1; //calculate result image cols

	result = Mat(result_rows, result_cols, CV_32FC1); //create mat to hold result of template match CV_8UC1
	//result.create( result_rows, result_cols, CV_32FC1 );
  
	matchTemplate(srcImg, templImg, result, TM_CCOEFF_NORMED); //perform template matching	TM_SQDIFF_NORMED

	normalize(result, result, 0.0, 1.0, NORM_MINMAX); //normalize the result NORM_MINMAX
	//normalize(result, result, 1.0, 0.0, NORM_MINMAX, -1, noArray() ); //normalize the result NORM_MINMAX
	
	//float max = result.at<float>(0,0);
	//float min = result.at<float>(0,0);
	cout.precision(5);
	cout << "Result size: " << result.rows << "," << result.cols << "(rows,cols)" << endl;
	
	double minVal; double maxVal; Point minLoc; Point maxLoc; //localize the best match with minMaxLoc
	minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
	
	//Note: Though x is the column variable, and y is the row variable, openCV Mats are in the form of (y,x)
	for (int x = 0; x < result.cols; x++)
	{
		for (int y = 0; y < result.rows; y++)
		{
			if(result.at<float>(y,x) >= 0.93)
			{
				cout << x+templImg.cols/2 << "," << y+templImg.rows/2 << ": " << result.at<float>(y,x) << endl;
			}
			/*
			if(result.at<float>(x,y) >= max)
			{
				max = result.at<float>(x,y);
			}
			if(result.at<float>(x,y) <= min)
			{
				min = result.at<float>(x,y);
			}
			*/
			
			
			
		}
		//cout << endl << endl;
	}
	
	//cout << "Max: " << scientific << max << endl;
	//cout << "Min: " << scientific << min << endl;

	
	
	
	cout<< "Max Val: " << scientific << maxVal << endl;
	cout<< "Min Val: " << scientific << minVal << endl;
	
	Point matchLoc = minLoc; //for SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
	matchLoc.x += templImg.cols/2; //center the match loc within the template
	matchLoc.y += templImg.rows/2; //center the match loc within the template
	return matchLoc;
}

int main() {

	Mat CSVImg, templateImg; //Create two Mat objects, one for the source image, one for the template
	Point matchPt; //Point object to hold match location
	CSVImg = Mat(150, 600, CV_8UC1); //Create 150x600px mat made of uint8 
	string CSVstr; //Temp string to hold line from csv file
	//ifstream myfile ("inputCSV/test_cacti1.csv"); //file to be opened
	ifstream myfile ("inputCSV/test_multi_dino.csv"); //file to be opened
	
	if(myfile) { //if file is valid
		for (int i=0; i<CSVImg.rows-1; i++) { //for each rows
			for (int j=0; j<CSVImg.cols-1; j++) { //for each column
				getline(myfile, CSVstr, ','); //get a line from the CSV up to the next comma
				CSVImg.at<uchar>(i,j) = stoi(CSVstr); //save the data from the CSV into an int
			}
		}
	}
	
	imwrite("output/csvimg.png", CSVImg); //write the original image to PNG for debug
	templateImg = imread("templatePNG/dino_template.png", IMREAD_GRAYSCALE ); //read the template image as a grayscale image
	matchPt = TemplateMatch(CSVImg, templateImg); //match the read CSV image to the template
	printf("MatchLoc = %d, %d \n", matchPt.x, matchPt.y); //print location of matched template to console	
	
	myfile.close(); //Close file
	return EXIT_SUCCESS;
}