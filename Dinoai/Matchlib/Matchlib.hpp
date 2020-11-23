#ifndef MATCHLIB_H
#define MATCHLIB_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <omp.h>
#include <stdio.h>

using namespace cv;

Point MatchingMethod(Mat srcImg, Mat templImg);

#endif