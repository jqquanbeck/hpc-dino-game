#ifndef MATCHLIB_H
#define MATCHLIB_H

#include <opencv2/opencv.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <omp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace cv;

vector<Point> TemplateMatch(Mat srcImg, Mat templImg, float tolerance);

#endif