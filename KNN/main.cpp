/**
 * @file main.cpp
 * @brief main function of knn programing exercise
 *
 * @author Tatsuya Harada
 * @date Nov. 5, 2011
 */
#include <cv.h>
#include <highgui.h>
#include <time.h>
#include <stdio.h>
#include <iostream>

#include "myknn.h"
#include "myutils.h"

using namespace cv;
using namespace std;


int main (int argc, char **argv)
{
  // file
  char *ftrain=(char *)"classification_train.dat"; //< training data file name
  char *ftrainidx=(char *)"classification_trainlabel.dat"; //< training label file name
  char *ftest=(char *)"classification_test.dat"; //< test data file name
  char *ftestidx=(char *)"classification_testlabel.dat"; //< training label file name

  // load data
  Mat trainmat=LoadMat(ftrain);
  Mat trainidxmat=LoadMat_i(ftrainidx);
  Mat testmat=LoadMat(ftest);
  Mat testidxmat=LoadMat_i(ftestidx);

  // // plot training data
  plotclusters2D(trainmat, trainidxmat, 2);

  // knn
  int nk=3; //< the number of k for k-nn
  Mat residxmat=Mat::zeros(testmat.rows,1,CV_32SC1); //< classification results
  MyKnn(trainmat, trainidxmat, testmat, residxmat, nk); //< knn

  // score
  double bingo=0; //< the number of hits
  int i;
  for(i=0;i<testmat.rows;i++){
    if(testidxmat.at<int>(0,i)==residxmat.at<int>(0,i)){
      bingo++;
    }
  }
  cout << "recognition rate: " << bingo/(testmat.rows)*100 << "%" << endl;

  return 0;
}
