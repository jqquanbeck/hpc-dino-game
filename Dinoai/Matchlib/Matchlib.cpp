#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <omp.h>
#include <stdio.h>

#include "Matchlib.hpp"

using namespace std;
using namespace cv;

Point MatchingMethod(Mat srcImg, Mat templImg) {
	
	Point matchLoc;
	Mat result;
	int result_cols =  srcImg.cols - templImg.cols + 1;
	int result_rows = srcImg.rows - templImg.rows + 1;

	result.create(result_rows, result_cols, CV_8UC1);
  
	matchTemplate(srcImg, templImg, result, TM_SQDIFF_NORMED); 

	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat() );

	double minVal; double maxVal; Point minLoc; Point maxLoc; //localize the best match with minMaxLoc
	minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
	matchLoc = minLoc; //for SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
	matchLoc.x += templImg.cols/2;
	matchLoc.y += templImg.rows/2;
	return matchLoc;
}