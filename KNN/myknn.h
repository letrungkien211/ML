/**
 * @file myknn.h
 * @brief k-nearest neighbor
 *
 * @author Tatsuya Harada
 * @date Nov. 5, 2011
 */
#ifndef MYKNN_H_INCLUDED
#define MYKNN_H_INCLUDED

#include <cv.h>
#include <highgui.h>
#include <time.h>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

void MyKnn(Mat&, Mat&, Mat&, Mat&, int);

#endif
