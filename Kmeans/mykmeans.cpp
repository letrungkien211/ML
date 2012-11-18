/**
 * @file mykmeans.cpp
 * @brief k-means
 *
 * @author Tatsuya Harada
 * @date Nov. 5, 2011
 */
#include "mykmeans.h"

/**
 * @brief k-means
 * 
 * @param mat Mat data matrix
 * @param nc the number of k of k-means
 * @param out_centmat Mat centroids (output)
 * @param out_idxmat Mat cluster index of mat (output)
 */

int NumIterations = 100;

void MyKmeans(Mat& mat, int nc, Mat& out_centmat, Mat& out_idxmat)
{
  /* 1. Initialization*/
  srand(time(NULL));
  int *matIndex = new int[mat.rows];

  for(int i = 0; i < mat.rows; ++i)
    matIndex[i] = 1;
  for(int i = 0; i< nc; i++){
    int tmp;
    do{
      tmp = rand()%mat.rows;
    }
    while(!matIndex[tmp]);
    cout <<tmp <<endl;
    
    mat.row(tmp).copyTo(out_centmat.row(i));
    matIndex[tmp] = 0;
  }

  /* Loop!*/
  Mat counter(out_centmat.rows, 1, CV_32SC1);
  for(int t = 0; t < NumIterations; t++){
    /*2. Assigment*/
    for(int i = 0; i< mat.rows; i++){
      double minDistance = norm(mat.row(i)-out_centmat.row(0));
      int minIndex = 0;
      for(int k = 1; k< nc; k++){
	float d = norm(mat.row(i)-out_centmat.row(k));
	if(d <minDistance){
	  minIndex = k;
	  minDistance = d;
	}
      }
      out_idxmat.at<int>(i,0) = minIndex;
    }
   
    /*3. Update*/     
    for(int i = 0; i<counter.rows; i++){
      counter.at<float>(i,0) = 0;
    }
    
    for(int i = 0; i <out_centmat.rows; i++){
      for(int j = 0; j <out_centmat.cols; j++){
	out_centmat.at<float>(i,j) = 0;
      }
    }
    
    for(int i=0; i<mat.rows; i++){
      out_centmat.row(out_idxmat.at<int>(i,0)) +=mat.row(i);
      cout << counter.at<int>(out_idxmat.at<int>(i,0),0)++<<endl;
    }
    
    cout <<counter.at<int>(0,0)<<endl;
    cout <<counter.at<int>(1,0)<<endl;
    cout <<out_centmat.row(0)<<endl;
    cout <<out_centmat.row(1)<<endl;
    
    out_centmat.row(0) = out_centmat.row(0)/counter.at<int>(0,0);
    out_centmat.row(1) = out_centmat.row(1)/counter.at<int>(1,0);
  }
}

