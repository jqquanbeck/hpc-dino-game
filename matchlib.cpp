#include <iostream>
#include <opencv2/opencv.hpp>

#include "matchlib.h"

using namespace std;
using namespace cv;

void matchlib(){
    cout << "Hello from matchlib" << endl;
}

vector<Point> TemplateMatch(Mat srcImg, Mat templImg, float threshold, float tolerance) {
	vector<Point> matchLocations;
	Point tempLoc;
	Mat result; //mat object to store the result of the template match algo	
	int result_rows = srcImg.rows - templImg.rows + 1; //calculate result image rows
	int result_cols = srcImg.cols - templImg.cols + 1; //calculate result image cols

	result = Mat(result_rows, result_cols, CV_32FC1); //create mat to hold result of template match CV_8UC1	
	
	matchTemplate(srcImg, templImg, result, TM_SQDIFF_NORMED); //perform template matching	 TM_CCOEFF_NORMED
	
	double minVal; double maxVal; Point minLoc; Point maxLoc; //localize the best match with minMaxLoc
	minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
	//cout << "("<< minLoc.x << "," << minLoc.y << ") = " << minVal << endl;
	
	for (int x = 0; x < result.cols; x++) {
		for (int y = 0; y < result.rows; y++) {
			if(result.at<float>(y,x) <= (1+tolerance)*threshold) { //If there are other locations where the result value is within tolerance% of the lowest, it's a second match.
				//cout << "("<< x << "," << y << ") = " << result.at<float>(y,x) << endl;
				tempLoc.x = x;
				tempLoc.y = y;
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

int getScore(Mat Img, bool isNight) { //Takes an unaltered image (e.g. not cropped) and determines the score
	//this will load the num_all.png image every time this function is called, which is super inefficient
		//Find some way to save that loading
		//probably just open the numbers once in main and pass them into the function each time?
		
	//The way this works is by using a sprite image which contains all digits 0-9 in a row
	//then the cropped image from the given screengrab is used as the template of the TM function
	//then where the highest value of the TM result is where the correct number is
	//basically instead of looking for each number within the extracted digit,
	//we look for where the extracted digit best matches an image containing each number
	
	int score = 0;
	int coords[][2] = {{547,20}, {536,20}, {525,20}, {514,20}, {503,20} }; //locations of the TOP LEFT corner of each score digit
	
	//using "smaller" sprite seems to give erroneous results. For such a easy TM, using the smaller sprite doesn't save much time anyway
	string numImgLoc;
	if (isNight == true) //nighttime
		numImgLoc = "../../dinosprite/fullsize/inverted/num_all.png"; 
	else //daytime
		numImgLoc = "../../dinosprite/fullsize/regular/num_all.png";
	
	Mat numImg = imread(numImgLoc, IMREAD_GRAYSCALE); //mat to hold the template numbers
	Mat scoreImg[5] = Mat(11, 9, CV_8UC1); //array of mats to hold the captured scores from the screenshot
	
	Mat result; //mat object to store the result of the template match algo
	
	//prepare image for template matching
	for(int digit = 0; digit < sizeof(scoreImg)/sizeof(scoreImg[0]); digit++) { //for each digit
		scoreImg[digit] = Img( Rect( coords[digit][0], coords[digit][1], 9, 11) ); //crop the image
		imwrite("output/scoreImg(" + to_string(digit) + ").png" , scoreImg[digit]); //write each score image to PNG for debug
	}
	
	for (int digit = 0; digit <= 4; digit++) { //for each digit
		matchTemplate(scoreImg[digit], numImg, result, TM_CCOEFF_NORMED); //perform template matching
		normalize(result, result, 0.0, 1, NORM_MINMAX); //normalize the result NORM_MINMAX
		
		//Random thought: does the range 0-1 imply that the *BEST* match is 1, or that a *PERFECT* match is a 1?
		//if somehow the input is screwed up and not actually the scoreboard of the game, will there still be a resultant 1?
		
		//Note: Though x is the column variable, and y is the row variable, openCV Mats are in the form of (y,x)
		int tempScoreLoc;	
		for (int x = 0; x < result.cols; x++) {
			for (int y = 0; y < result.rows; y++) {
				if(result.at<float>(y,x) == 1) {
					//cout << "(" << x << "," << y << ") = " << result.at<float>(y,x) << "\t(Digit = " << digit << ")" << endl;
					tempScoreLoc = x;
				}
			}
		}
		
		int factor = (tempScoreLoc+1) / 10; //thanks joel
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
	
	myfile.close();
	
	return CSVImg;
}

unsigned char ** CSVtoArr(int rows, int cols, string filepath) {
	//this function sucks because it doesn't automatically determine size of CSV
	//find some way to make the mat automatically the size of the CSV without much overhead.
	
	/*
	unsigned char ** arr[rows][cols];
	ifstream myfile(filepath); //open csv file
	
	string CSVstr; //temp to hold a line from the csv file
	
	if(myfile) { //if file is valid
		for (int i=0; i < rows-1; i++) { //for each row
			for (int j=0; j < cols-1; j++) { //for each column
				getline(myfile, CSVstr, ','); //get a line from the CSV up to the next comma
				arr[i][j] = (unsigned char)stoi(CSVstr); //save the data from the CSV into an int
			}
		}
	}
	
	return arr;
	*/
}	

enemy_t getEnemy(Mat Img, float tolerance, bool isNight) {
	Mat result;

	string filePath = "../../dinosprite/smaller/regular/";
	string fileName[] = {"cacti_single_large.png", "cacti_single_small.png", "cacti_2x_large.png", "cacti_2x_small.png", "cacti_quad.png", "cacti_trio.png", "bird_1.png", "bird_2.png"};\
	float thresholds[] = {0.0119287, 0.0119287, 0.0119287, 0.0119287, 0.0119287, 0.0119287, 0.0119287, 0.0119287}; //only the cacti_single_large is actually real 
	//the rest may(?) need to be determined manually by sampling a screenshot known to have a given sprite on it
	vector<Point> EnemyLoc[8];
	
	for( int i = 0; i < sizeof(fileName)/sizeof(fileName[0]); i++) { //iterate through each sprite
		Mat enemyTemplate = imread(filePath+fileName[i], IMREAD_GRAYSCALE);
		EnemyLoc[i] = TemplateMatch(Img, enemyTemplate, 0.0119287, 0.05);
		
		if(EnemyLoc[i].size() != 0)
			cout << "Match(es) found!! File: " << fileName[i] << ", Number of matches = " << EnemyLoc[i].size() << ". Locations: ";
		for(int j = 0; j < EnemyLoc[i].size(); j ++) {
			cout << "(" << EnemyLoc[i].at(j).x << "," << EnemyLoc[i].at(j).y << ")  ";
		}
		if(EnemyLoc[i].size() != 0)
			cout << endl;
	}
	

		

		
	enemy_t asdf = {69, 420, 99}; //return so it doesn't break
	return asdf;
} 