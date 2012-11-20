
#include <cv.h>
#include <string>

using namespace std;
using namespace cv;

#include "createdata.hpp"

void Unroll(const Mat &src, Mat &des){
    int rows = src.rows;
    int cols = src.cols;
    des= Mat::zeros(1, rows*cols, CV_32F);
    for(int i = 0, rows = src.rows; i< rows; ++i){
	for(int j = 0, cols = src.cols; j< cols; j++){
	    des.at<float>(i*cols+j) = src.at<float>(i,j);
	}
    }
}


void CreateData(const string &dataFileName, const string& labelFileName,
		Mat &trainData, Mat & trainLabel,int numData){
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


int main(int argc, char* argv[]){
    string dataFileName(argv[1]);
    string labelFileName(argv[2]);
    int numData = atoi(argv[3]);
    Mat trainData, trainLabel;

    CreateData(dataFileName, labelFileName, trainData, trainLabel, numData);
    return 0;
}



