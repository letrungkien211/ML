#ifndef CREATE_DATA_HPP
#define CREATE_DATA_HPP
#include <cv.h>
#include <string>

using namespace std;
using namespace cv;

void CreateData(const string &dataFileName, const string& labelFileName,
		Mat &trainData, Mat & trainLabel,int numData);

void Unroll(const Mat &src, Mat &des);

#endif

