#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <omp.h>
#include <stdio.h>
#include "Matchlib/Matchlib.hpp"

using namespace std;
using namespace cv;

//int main1();
int main2();
int main3();
int main4();
int main5();



int main() {
	main5();
	return 0;
}

int main5() {
	
	//Mat testImg = CSVtoMat(150, 600, "../Screenshots_Joel/img_108.csv");
	//int dinoheight = dinoHeight(testImg, 0);
	int dinoheight;
	cout << "dinoheight from main = " << dinoheight << endl;
	
		string filePath = "../Screenshots_Joel/"; //path string
	
	for(int k = 0; k < 355; k++) {
		string fileName = "img_" + to_string(k) + ".csv"; //create filename string
		string fullFileName = filePath+fileName;
		
		Mat testImg = CSVtoMat(150, 600, fullFileName);
		dinoheight = dinoHeight(testImg, 0);
		cout << "img #" << k << " " << "dinoheight from main = " << dinoheight << endl;

	}
	
	return 0;
}

int main4() {
	//Mat testImg = CSVtoMat(150, 600, "../Screenshots_Joel/img_108.csv");
	//enemy_t * enemyArr = (enemy_t*)malloc(6*sizeof(enemy_t*));
	enemy_t * enemyArr = (enemy_t*)malloc((6+1)*sizeof(enemy_t)); //the +1 fixes a memory issue i guess
	cout << "test" << endl;
	string filePath = "../Screenshots_Joel/"; //path string
	
	for(int k = 0; k < 355; k++) {
		cout << k << endl;
		string fileName = "img_" + to_string(k) + ".csv"; //create filename string
		string fullFileName = filePath+fileName;
		
		Mat testImg = CSVtoMat(150, 600, fullFileName);
		//cout << "test" << endl;
		enemyArr = getEnemy(testImg, 0.05, 0, 6);
		for(int i = 0; i < 6; i++) {
			if(enemyArr[i].ID != 999) {
				cout << "Enemy found in image" << k << "! Located at: (" << enemyArr[i].x << "," << enemyArr[i].y << ") ID: " << enemyArr[i].ID << endl;
			}
		}
		
		
	}
	
	free(enemyArr);
	
	
	/*
	Current map of enemy IDs
	0 = cacti_single_large.png
	1 = cacti_single_small.png
	2 = cacti_2x_large.png
	3 = cacti_2x_small.png
	4 = cacti_quad.png
	5 = cacti_trio.png
	6 = bird_1.png
	7 = bird_2.png
	999 = No enemy found
	*/
	
	/*
	for (int k = 0; k < 355; k++) {
		string filePath = "../Screenshots_Joel/"; //path string
		string fileName = "img_" + to_string(k) + ".csv"; //create filename string
		string fullFileName = filePath+fileName;
		cout << k << " ";
		testImg = CSVtoMat(150, 600, fullFileName);
		
		enemyArr = getEnemy(testImg, 0.05, 0);
		//cout << "Image " << k << ":" << test << endl;
	}
	*/
	return 0;
}

/*
int main1()
{
	Mat CSVImg, templateImg; //Create two Mat objects, one for the source image, one for the template
	Point matchPt; //Point object to hold match location
	vector<Point> matchPts;
	CSVImg = Mat(150, 600, CV_8UC1); //Create 150x600px mat made of uint8
	string CSVstr; //Temp string to hold line from csv file
	ofstream logfile("log.txt", ios::trunc); //log file name, truncated as to rewrite the log file each time the code is run
	
	
	//string file = "../Screenshots_Joel/inverted.csv";
	string file = "../Screenshots_Joel/img_10.csv";

	ifstream myfile(file); //open csv

	if(myfile) { //if file is valid
		for (int i=0; i<CSVImg.rows-1; i++) { //for each row
			for (int j=0; j<CSVImg.cols-1; j++) { //for each column
				getline(myfile, CSVstr, ','); //get a line from the CSV up to the next comma
				CSVImg.at<uchar>(i,j) = stoi(CSVstr); //save the data from the CSV into an int
			}
		}
	}
	
	bool nightState = isNight(CSVImg);
	cout << "nightState: " << nightState << endl;
	
	
	for (int k = 0; k < 355; k++) {
		
		string filePath = "../Screenshots_Joel/"; //path string
		string fileName = "img_" + to_string(k) + ".csv"; //create filename string
		string fullFileName = filePath+fileName;
		
		ifstream myfile(fullFileName); //open csv
		
		if(myfile) { //if file is valid
			for (int i=0; i<CSVImg.rows-1; i++) { //for each row
				for (int j=0; j<CSVImg.cols-1; j++) { //for each column
					getline(myfile, CSVstr, ','); //get a line from the CSV up to the next comma
					CSVImg.at<uchar>(i,j) = stoi(CSVstr); //save the data from the CSV into an int
				}
			}
		}
		else { //throw simple error if file isn't found
			cout << "ERROR in reading file!" << endl;	
		}
		
		if(k == 0 || k == 5 || k == 6 || k == 7 || k == 8 || k == 9 || k == 10 || k == 100) {
			string savefileLoc = "output/";
			string savefile = "img_" + to_string(k) + ".png";
			cout << savefile << endl;
			imwrite(savefileLoc+savefile, CSVImg); //write the original image to PNG for debug
		}
		
		string templFileLoc;
		if(nightState == false) {
			templFileLoc = "../../dinosprite/fullsize/regular/";
		}
		else {
			templFileLoc = "../../dinosprite/fullsize/inverted/";
		}
			
		templateImg = imread("../CSVTemplateMatch/templatePNG/dino_template.png", IMREAD_GRAYSCALE); //read the template image as a grayscale image
		
		matchPts = TemplateMatch(CSVImg, templateImg, 0.99); //match the read CSV image to the template
		
		logfile << "File path: " << filePath << endl;
		for (int j = 0; j < matchPts.size(); j++) { //for all of the matched points
			//printf("(%d, %d)\t", matchPts[i].x, matchPts[i].y);
			logfile << fileName << ": ";
			logfile << "(" <<  matchPts[j].x << "," << matchPts[j].y << ")   ";
		}
		logfile << "\n"; 
		
		myfile.close(); //Close file
	}
	
	logfile.close();
	
	return EXIT_SUCCESS;
}
*/

int main2() {
	Mat testImg = Mat(150, 600, CV_8UC1);
	//string filePath = "../Screenshots_Joel/img_95.csv"; //path string
	string filePath = "../Screenshots_Joel/img_107.csv"; //path string
	testImg = CSVtoMat(150, 600, filePath);
	int test = 0;

	for (int k = 0; k < 355; k++) {
		string filePath = "../Screenshots_Joel/"; //path string
		string fileName = "img_" + to_string(k) + ".csv"; //create filename string
		string fullFileName = filePath+fileName;
		testImg = CSVtoMat(150, 600, fullFileName);
		
		test = getScore(testImg, false);
		cout << "Image " << k << ":" << test << endl;
	}
	
	return EXIT_SUCCESS;
}

int main3() {
	/*
	char 
	CSVtoArr(150, 600);
	
	return EXIT_SUCCESS;
	*/
}

