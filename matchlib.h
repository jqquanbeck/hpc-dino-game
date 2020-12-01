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

typedef struct {
	uint32_t x, y;
	uint32_t ID;
} enemy_t;

std::vector<Point> TemplateMatch(Mat srcImg, Mat templImg, float threshold, float tolerance);

uint32_t isNight(Mat Img);

uint32_t getScore(Mat Img, bool isNight);

Mat CSVtoMat(int rows, int cols, std::string filepath);

unsigned char ** CSVtoArr(int rows, int cols);

enemy_t * getEnemy(Mat Img, float tolerance, bool isNight, int maxEnemies);

uint32_t dinoHeight(Mat Img, bool isNight);

#endif