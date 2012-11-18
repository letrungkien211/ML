/**
 * @file myutils.h
 * @brief utility functions for OpenCV
 *
 * @author Tatsuya Harada
 * @date Nov. 5, 2011
 */
#ifndef MYUTILS_H_INCLUDED
#define MYUTILS_H_INCLUDED

#include <cv.h>
#include <highgui.h>
#include <time.h>
#include <stdio.h>

using namespace cv;
using namespace std;

Mat LoadMat (char*);
Mat LoadMat_i (char*);
void plotclusters2D(Mat&, Mat&, int);

#endif
