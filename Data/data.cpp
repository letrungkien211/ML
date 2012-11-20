#include "data.hpp"
#include <string>
#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
using namespace cv;
using namespace Utils;

void Data::Image2Matrix(const string &dirName, 
			const string &imgFileName,
			const string &outputFileName, 
			int imgNum){
    char fname[100];
    char nodename[100];
    sprintf(fname, "%s/%s.xml", dirName.c_str(), outputFileName.c_str());
    FileStorage cbfs(fname, CV_STORAGE_WRITE);

    for(int i = 1; i<imgNum; i++){
	cout << i << endl;
	sprintf(fname, "%s/%s%04d.jpg", dirName.c_str(), imgFileName.c_str(),i);
	Mat cimg = imread(fname);
	cout << fname <<endl;
	Mat gimg;
	cvtColor(cimg, gimg,CV_RGB2GRAY);
	Mat fimg;
	gimg.convertTo(fimg, CV_32F);
	fimg/=255;
	sprintf(nodename, "data_%04d", i);
	cbfs << string(nodename) << fimg;
    }
}


void Data::Load(const string &dataFileName, 
		const string& labelFileName,
		Mat &trainData, 
		Mat & trainLabel,
		int numData)
{
    FileStorage dataFile(dataFileName, CV_STORAGE_READ);
    FileStorage labelFile(labelFileName, CV_STORAGE_READ);

    labelFile["label"] >> trainLabel;
    char str[100];
    for(int i = 1 ; i<numData; i++){
	sprintf(str, "data_%04d", i);
	Mat data;
	dataFile[str] >> data;
	Mat tmp;
	Unroll(data, tmp);
	trainData.push_back(tmp);
    }
}


