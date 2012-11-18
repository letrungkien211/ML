/**
 * @file mykmeans.h
 * @brief k-means
 *
 * @author Tatsuya Harada
 * @date Nov. 5, 2011
 */
#ifndef MYKMEANS_H_INCLUDED
#define MYKMEANS_H_INCLUDED

#include <cv.h>
#include <highgui.h>
#include <time.h>
#include <stdio.h>
#include <iostream>

#define KMEANS_MAX_ITER 100

using namespace cv;
using namespace std;


void MyKmeans(Mat&, int, Mat&, Mat&);

#endif
