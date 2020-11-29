#ifndef MATCHLIB_H
#define MATCHLIB_H

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

namespace matchlib{
    void matchlib();
    bool isNight(Mat Img);
    vector<Point> TemplateMatch(Mat srcImg, Mat templImg, float tolerance);
}

#endif