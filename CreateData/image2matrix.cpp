#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <cstdio>
#include <vector>

#include "image2matrix.hpp"

using namespace std;
using namespace cv;

void Image2Matrix(const string &dirName, const string &imgFileName,
		  const string &outputFileName, int imgNum){
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



int main(int argc, char **argv){
    string dirName(argv[1]);
    string imgFileName(argv[2]);
    string outputFileName(argv[3]);
    int imgNum = atoi(argv[4]);

    Image2Matrix(dirName, imgFileName, outputFileName, imgNum);
    return 0;
}
