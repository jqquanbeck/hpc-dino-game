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

uint32_t isNight(Mat Img)
{
	//Samples are (413,25), (422, 22), and (407,20)
	//These lie between the H and I, in the crook of the I, and in the crook of the H, respectively
	int coords[][2] = { {413, 25}, {422, 22}, {407, 20} };
	int avg = 0;
	int numPoints = (int)( sizeof(coords) / sizeof(coords[0]) );
	
	for (int i = 0; i < numPoints; i++) {
		avg += (int)Img.at<uchar>( coords[i][1], coords[i][0] );
	}
	avg /= numPoints;
	
	if(avg <= 128) {
		return (uint32_t) 1;
	}
	else {
		return (uint32_t) 0;
	}
}

uint32_t getScore(Mat Img, bool isNight) { //Takes an unaltered image (e.g. not cropped) and determines the score
	//this will load the num_all.png image every time this function is called, which is super inefficient
		//Find some way to save that loading
		//probably just open the numbers once in main and pass them into the function each time?
		
	//The way this works is by using a sprite image which contains all digits 0-9 in a row
	//then the cropped image from the given screengrab is used as the template of the TM function
	//then where the highest value of the TM result is where the correct number is
	//basically instead of looking for each number within the extracted digit,
	//we look for where the extracted digit best matches an image containing each number
	
	uint32_t score = 0;
	int coords[][2] = {{547,20}, {536,20}, {525,20}, {514,20}, {503,20} }; //locations of the TOP LEFT corner of each score digit
	
	//using "smaller" sprite seems to give erroneous results. For such a small TM, using the smaller sprite doesn't save much time anyway
	string numImgLoc;
	if (isNight == true) //nighttime
		numImgLoc = "Resources/fullsize/inverted/num_all.png"; 
	else //daytime
		numImgLoc = "Resources/fullsize/regular/num_all.png"; 
	
	Mat numImg = imread(numImgLoc, IMREAD_GRAYSCALE); //mat to hold the template numbers
	Mat scoreImg[5] = Mat(11, 9, CV_8UC1); //array of mats to hold the captured scores from the screenshot
	
	Mat result; //mat object to store the result of the template match algo
	
	//prepare image for template matching
	for(unsigned int digit = 0; digit < sizeof(scoreImg)/sizeof(scoreImg[0]); digit++) { //for each digit
		scoreImg[digit] = Img( Rect( coords[digit][0], coords[digit][1], 9, 11) ); //crop the image
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
		score += (uint32_t) factor*pow(10,digit);
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
	return 0;
}	

enemy_t * getEnemy(Mat Img, float tolerance, bool isNight, int maxEnemies) {
	//If there are more matches on screen than maxEnemies allows for, the matches are returned in prioritiy based on the order of the fileName string 
	//(e.g. cacti_single_large has higher priority than bird_2)
	//The amount of returned matches had to be constrained because the NN has to have a known input size

	//enemy_t * enemyStruct = (enemy_t*) malloc( maxEnemies * sizeof(enemy_t*) ); //initialize 
	enemy_t * enemyStruct = (enemy_t*) malloc( (maxEnemies+1) * sizeof(enemy_t) ); //initialize. The +1 fixes a memory issue i guess
	
	//these should probably be stored in a struct but too bad
	if(isNight == true) {
		string filePath = "Resources/smaller/inverted/";
	}
	else {
		string filePath = "Resources/smaller/regular/";
	}
	string fileName[] = {"cacti_single_large.png", "cacti_single_small.png", "cacti_2x_large.png", "cacti_2x_small.png", "cacti_quad.png", "cacti_trio.png", "bird_1.png", "bird_2.png"};
	float thresholds[] = {0.0119287, 0.0119287, 0.0119287, 0.0119287, 0.0119287, 0.0119287, 0.0119287, 0.0119287}; 
	
	//only the cacti_single_large is a real number. 
	//The rest should probably be filled out based on testing on screencaps where a given sprite is known to exist
	
	vector<Point> EnemyLoc[8]; //8 vectors of points for 8 sprites. should be defined based on size of file name lol
	
	for(unsigned int i = 0; i < sizeof(fileName)/sizeof(fileName[0]); i++) { //iterate through each sprite
		Mat enemyTemplate = imread(filePath+fileName[i], IMREAD_GRAYSCALE); //read the sprite
		EnemyLoc[i] = TemplateMatch(Img, enemyTemplate, thresholds[i], tolerance); //match the sprite with the provided image
	}
	
	int enemyNumber = 0; //this stores how many enemies have been matched
	
	//probably not the best way to do this?
	for(unsigned int i = 0; i <  sizeof(fileName)/sizeof(fileName[0]); i++) { //for each sprite
		for(unsigned int j = 0; j < EnemyLoc[i].size(); j ++) { //for each match of that sprite (enemyloc.size() could be 0!)
			if(enemyNumber < maxEnemies) {
				enemyStruct[enemyNumber].x =  (uint32_t) EnemyLoc[i].at(j).x;
				enemyStruct[enemyNumber].y =  (uint32_t) EnemyLoc[i].at(j).y;
				enemyStruct[enemyNumber].ID = (uint32_t) i;
				enemyNumber++;
			}
		}
	}
	
	if(enemyNumber < maxEnemies) { //if you didn't use up all the available enemy slots
		for(int k = maxEnemies; k >= enemyNumber; k--) { //fill the rest with junk info
			enemyStruct[k].x =  (uint32_t) 999;
			enemyStruct[k].y =  (uint32_t) 999;
			enemyStruct[k].ID = (uint32_t) 8;
		}
	}
	
	//this can probably be removed. Its supposed to free the memory used by enemyloc
	for( int i = 0; i < 8; i++) {
		vector<Point>().swap(EnemyLoc[i]);
	}

	return enemyStruct;
} 

uint32_t dinoHeight(Mat Img, bool isNight) {
	
	string filePath;
	if (isNight == true)
		filePath = "Resources/smaller/inverted/dino_head.png";
	else
		filePath = "Resources/smaller/regular/dino_head.png";
	
	Mat dinoTemplate = imread(filePath, IMREAD_GRAYSCALE); //read the sprite
	
	vector<Point> dino;
	
	dino = TemplateMatch(Img, dinoTemplate, 0.0119287, 0.5); //match the sprite with the provided image at 50% tolerance
	
	if(dino.size() != 0) //if there is a match
		return (uint32_t)dino.at(0).y;
	else //if there's no match
		return (uint32_t) 0; //return garbage
	
	
}
