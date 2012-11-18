/**
 * @file main.cpp
 * @brief main function of k-means programing exercise
 *
 * @author Tatsuya Harada
 * @date Nov. 5, 2011
 */
#include <cv.h>
#include <highgui.h>
#include <time.h>
#include <stdio.h>
#include <iostream>

#include "mykmeans.h"
#include "myutils.h"

using namespace cv;
using namespace std;


int main (int argc, char **argv)
{
  // load data
  char *fname=(char *)"faithful.dat";
  Mat mat=LoadMat(fname);

  // k-means
  int nc=2; //< the number of clusters
  Mat centmat=Mat::zeros(nc,mat.cols,CV_32FC1); //< centroid matrix
  Mat idxmat=Mat::zeros(mat.rows,1,CV_32SC1); //< index matirx of data
  MyKmeans(mat,nc,centmat,idxmat); //< k-means
  cout << centmat << endl;

  // plot clusters
  plotclusters2D(mat,idxmat,nc);

  return 0;
}
