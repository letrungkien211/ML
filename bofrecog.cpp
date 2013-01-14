/**
 * @file bofrecog.cpp
 * @brief generic image recognition with BoF and knn
 *
 * @author Tatsuya Harada
 * @date Oct. 30, 2010
 */

#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

const int SDIM = 64; //< dimension of SURF

void printMat_f(Mat mat)
{
  for(int i=0;i<mat.rows;i++){
    for(int j=0;j<mat.cols;j++){
      cout << mat.at<float>(i,j)<< " ";
    }
    cout << endl;
  }
  cout << endl;
}

void printMat_i(Mat mat)
{
  for(int i=0;i<mat.rows;i++){
    for(int j=0;j<mat.cols;j++){
      cout << mat.at<int>(i,j)<< " ";
    }
    cout << endl;
  }
  cout << endl;
}

void calc_bof(Mat& descmat, Mat& codebook, Mat& bofmat)
{
  // Insert your codes!
  
  bofmat=bofmat/(float)descmat.rows; //< normalize
}


void KNearestNeighbor(Mat& trainmat, Mat& trainclassmat, Mat& testmat, Mat& testclassmat, int nk)
{
  int nc=0; //< the number of classes
  for(int i=0; i<trainclassmat.rows; i++){
    if(trainclassmat.at<int>(i,0)>nc){
      nc=trainclassmat.at<int>(i,0);
    }
  }
  nc++;
  
  Mat distmat=Mat::zeros(testmat.rows,trainmat.rows,CV_32F); //< distance matrix
  for(int i=0;i<testmat.rows;i++){
    Mat tmpmat1=testmat.row(i);
    for(int j=0;j<trainmat.rows;j++){
      Mat tmpmat2=(trainmat.row(j)-tmpmat1);
      distmat.at<float>(i,j)=(float)tmpmat2.dot(tmpmat2);
    }
  }
  Mat idxmat;
  sortIdx(distmat,idxmat,CV_SORT_EVERY_ROW+CV_SORT_ASCENDING);

  Mat votingmat=Mat::zeros(testmat.rows,nc,CV_32S); //< voting matrix
  for(int i=0; i<testmat.rows; i++){
    for(int j=0; j<nk; j++){
      int idx=idxmat.at<int>(i,j); //< idx: sample# of k nearest neighbors
      int c=trainclassmat.at<int>(idx,0); //< c: class
      votingmat.at<int>(i,c)+=1;
    }
  }

  Mat maxidxmat=Mat::zeros(testmat.rows,1,CV_32S);
  sortIdx(votingmat,maxidxmat,CV_SORT_EVERY_ROW+CV_SORT_DESCENDING);
  testclassmat=maxidxmat.col(0);
}


int main (int argc, char **argv)
{
  const int nk = argc > 1 ? atoi(argv[1]) : 1; //< k for knn
  const char *cbname = argc > 2 ? argv[2] : "codebook.xml"; //< codebook file name


  int nc=15; //< the number of classes
  int ntrain=25; //< the number of training data in each category
  int ntest=30-ntrain; //< the number of test data in each category
  int nd; //< the number of data in each category
  char cname[][128] = { "Faces" , "camera" , "car_side" , "chair" , "cup" , "dalmatian" , "grand_piano" , "hedgehog" , "lamp" , "laptop" , "panda" , "pizza" , "soccer_ball" , "tick" , "watch"}; //< class name
  char fname[256]; //< image file name 
  char *dir=(char *)"../caltech15/"; //< test data directory


  
  // Open File Storage
  cv::FileStorage cbfs(cbname,CV_STORAGE_READ);
  cv::FileNode node(cbfs.fs, NULL); //< top node
  Mat cent;
  cv::read(node["cent"],cent);

  // create window
  char winname[] = "Bag of Features";
  namedWindow( winname, CV_WINDOW_AUTOSIZE );

  // initialize surf
  vector<KeyPoint> key_v; //< keypoints
  vector<float> desc_v; //< descriptors
  SURF surf_i = SURF(500,4,2,false); // true: 128dim, false: 64dim

  // Bag of Features
  Mat trainbofmat=Mat::zeros(ntrain*nc,cent.rows,CV_32F);
  Mat testbofmat=Mat::zeros(ntest*nc,cent.rows,CV_32F);
  // Label matrix
  Mat trainlabelmat=Mat::zeros(ntrain*nc,1,CV_32S);
  Mat testlabelmat=Mat::zeros(ntest*nc,1,CV_32S);

  int sidx; //< start index
  int idx;

  for(int t=0;t<2;t++){
    if(t==0){ //< for training
      sidx=1;
      nd=ntrain;
      idx=0;
    }
    else{ //< for testing
      sidx=ntrain+1;
      nd=ntest;
      idx=0;
    }
    for(int i=0;i<nc;i++){
      for(int j=sidx;j<sidx+nd;j++){
	// load image
	sprintf(fname,"%s%s/image_%04d.jpg",dir,cname[i],j);
	cout << fname << endl;
	Mat cimg = imread(fname);

	// convert color image to gray scale image
	Mat gimg;
	cvtColor(cimg, gimg, CV_BGR2GRAY);

	// extract surf
	surf_i(gimg, Mat(), key_v, desc_v);
      
	// convert vector to matrix. descmat1: n_keypoints x dim
	Mat descmat=Mat(desc_v).reshape(0,desc_v.size()/SDIM);

	// build BoF
	if(t==0){ // for training
	  Mat boftmp=trainbofmat.row(idx);
	  calc_bof(descmat, cent, boftmp);
	  trainbofmat.row(idx)=boftmp;
	  trainlabelmat.at<int>(idx,0)=i;
	}
	else if(t==1){ // for testing
	  Mat boftmp=testbofmat.row(idx);
	  calc_bof(descmat, cent, boftmp);
	  testbofmat.row(idx)=boftmp;
	  testlabelmat.at<int>(idx,0)=i;
	}
	idx++;
      }
    }
  }

  // recognition with knn
  Mat reslabelmat=Mat::zeros(testbofmat.rows,1,CV_32S);
  KNearestNeighbor(trainbofmat, trainlabelmat, testbofmat, reslabelmat, nk);
  
  // scoring
  int bingo=0;
  idx=0;
  for(int i=0;i<nc;i++){
    for(int j=0;j<ntest;j++){
      if(reslabelmat.at<int>(idx,0)==testlabelmat.at<int>(idx,0)){
	bingo++;
      }
      cout << reslabelmat.at<int>(idx,0) << " ";
      idx++;
    }
    cout << endl;
  }
  cout << "Recognition rate [%]: " << (float)bingo/(float)idx*100 << endl;

  return 0;
}
