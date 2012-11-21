#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <cv.h>

#include "utils.hpp"

using namespace std;
using namespace cv;

class Data{
public:
    static void Load(const string &dataFileName, 
		     const string &labelFileName,
		     Mat &trainData, 
		     Mat & trainLabel,
		     int numData);
    static void Image2Matrix(const string &dirName, 
			     const string &imgFileName,
			     const string &outputFileName, 
			     int imgNum);

};

#endif
