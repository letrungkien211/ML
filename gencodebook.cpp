/**
 * @file gencodebook.cpp
 * @brief codebook generation code
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

int main (int argc, char **argv)
{
    const int nclusters = argc > 1 ? atoi(argv[1]) : 100; //< # of codewords
    const char *cbname = argc > 2 ? argv[2] : "codebook.xml"; //< codebook file name

    int nc=15; //< the number of classes
    int ntrain=25; //< the number of training data in each category
    char cname[][128] = { "Faces" , "camera" , "car_side" , "chair" , "cup" , "dalmatian" , "grand_piano" , "hedgehog" , "lamp" , "laptop" , "panda" , "pizza" , "soccer_ball" , "tick" , "watch"}; //< class name
    char fname[256]; //< image file name 
    char *traindir=(char *)"../caltech15/"; //< training data directory


    // create window
    char winname[] = "codebook generation";
    namedWindow( winname, CV_WINDOW_AUTOSIZE );

    // initialize surf
    vector<KeyPoint> key_v; //< keypoints
    vector<float> desc_v; //< descriptors
    vector<float> desc_vall; //< descriptors

    SURF surf_i = SURF(500,4,2,false); // true: 128dim, false: 64dim
    vector<KeyPoint>::iterator it; //< iterators of keypoints


    for(int i=0;i<nc;i++){
	for(int j=0;j<ntrain;j++){
	    desc_vall.clear();
	    key_v.clear();
	    // load image
	    sprintf(fname,"%s%s/image_%04d.jpg",traindir,cname[i],j+1);
	    Mat cimg = imread(fname);

	    // convert color image to gray scale image
	    Mat gimg;
	    cvtColor(cimg, gimg, CV_BGR2GRAY);

	    // extract surf
	    surf_i(gimg, Mat(), key_v, desc_v);
	    desc_vall.insert(desc_vall.end(),desc_v.begin(),desc_v.end());
      
	    // draw keypoints
	    for(it = key_v.begin(); it!=key_v.end(); ++it)
		circle(cimg, Point(it->pt.x, it->pt.y),(int)(it->size/3), Scalar(255,255,0));
      
	    imshow(winname, cimg);
	    cvWaitKey(10);
	}
    }

    // convert vector to matrix. descmat1: n_keypoints x dim
    Mat descmat=Mat(desc_vall).reshape(0,desc_vall.size()/SDIM); //< reshape: strange behavior!!!

    // k-means clustering
    cout << "clustering ..." << endl;
    Mat cidx; //< index
    Mat cent; //< centroids, codewords

    //*****************************************************************
    kmeans(descmat, nclusters, cidx,
	   cvTermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 10, 1.0),
	   1, KMEANS_PP_CENTERS, cent);
    // Insert your codes!
    //*****************************************************************

    // save codebook
    cout << "saving codebook ..." << endl;
    cv::FileStorage fs(cbname,CV_STORAGE_WRITE);
    cv::write(fs,"cent",cent);
  
    return 0;
}
