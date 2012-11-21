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

    cout << "Start Image2Matrix" <<endl;
    for(int i = 0; i<imgNum; i++){
	sprintf(fname, "%s/%s%04d.jpg", dirName.c_str(), imgFileName.c_str(),i+1);
	cout << fname <<endl;
	Mat cimg = imread(fname);
	Mat gimg;
	cvtColor(cimg, gimg,CV_RGB2GRAY);
	Mat fimg;
	gimg.convertTo(fimg, CV_32F);
	fimg/=255;
	sprintf(nodename, "%s%04d", outputFileName.c_str(), i);
	cbfs << string(nodename) << fimg;
    }
}


void Data::Load(const string &dataFileName, 
		const string &labelFileName,
		Mat &trainData, 
		Mat &trainLabel,
		int numData)
{
    FileStorage dataFile(dataFileName, CV_STORAGE_READ);
    FileStorage labelFile(labelFileName, CV_STORAGE_READ);

    labelFile["mnistlabel"] >> trainLabel;

    numData = max(numData, trainLabel.rows);
    char str[100];
    for(int i = 0 ; i<numData; i++){
	sprintf(str, "%s%04d", "mnistdata", i);
	cout <<str<<endl;
	Mat data;
	dataFile[str] >> data;
	if(i==0){
	    if(trainData.rows!=numData || trainData.cols!=data.rows*data.cols)
		trainData = Mat::zeros(numData, data.rows*data.cols, CV_32F);
	}
	Mat tmp;
	Unroll(data, tmp);
	//cout << tmp<<endl;
	tmp.copyTo(trainData.row(i));
    }
}

