/**
 * @file myknn.cpp
 * @brief k-nearest neighbor
 *
 * @author Tatsuya Harada
 * @date Nov. 5, 2011
 */

#include "myknn.h"

/**
 * @brief k-nearest neighbor
 * 
 * @param trainmat cv::Mat training data
 * @param trainidxmat cv::Mat labels of training data
 * @param testmat cv::Mat test data
 * @param residxmat cv::Mat estimated labels of test data (return value)
 * @param nk the number of k for KNN
 */

int NumIterations = 10000;

void MyKnn(Mat& trainmat, Mat& trainidxmat,
	   Mat& testmat, Mat& residxmat, int nk)
{
  Mat distance(trainmat.rows, 1,CV_32SC1);
  int *index = new int[trainmat.rows];
  float d;

  for(int i = 0; i < testmat.rows; i++){
    
    // Distance 
    for(int j = 0; j< trainmat.rows; j++){
      Mat tmp = trainmat.row(j)-testmat.row(i);
      distance.at<float>(j,0) = norm(tmp);
      cout << j<< ": " <<distance.at<float>(j,0)<<endl;
    }
      
    // Sort
    for(int j = 0; j< trainmat.rows; j++)
      index[j] = j;


    float tmp1, tmp2;
    for(int j = 0; j< trainmat.rows-1; j++){
      for(int k = j+1; k< trainmat.rows; k++){
	if(distance.at<float>(k,0)<distance.at<float>(j,0)){
	  tmp1 = distance.at<float>(j,0);
	  distance.at<float>(j,0) = distance.at<float>(k,0);
	  distance.at<float>(k,0) = tmp1;
	  
	  tmp2 = index[j];
	  index[j] = index[k];
	  index[k] = tmp2;
	}
      }
    }

    // Assignment
    int counter = 0;
    for(int k = 0; k<nk; k++)
      counter += trainidxmat.at<int>(index[k],0);
    residxmat.at<int>(i,0) = counter>nk/2 ? 1 : 0;

  }

  delete index;
}
