#include <cv.h>
#include <Eigen/Dense>
#include <string>
#include <highgui.h>

#include "utils.hpp"

namespace Utils{

    using namespace cv;
    using namespace std;
    using namespace Eigen;

    void Unroll(const Mat &src, Mat &des){
	int rows = src.rows;
	int cols = src.cols;
	if(des.rows!=1 || des.cols!=rows*cols)
	    des= Mat::zeros(1, rows*cols, CV_32F);
	for(int i = 0, rows = src.rows; i< rows; ++i){
	    for(int j = 0, cols = src.cols; j< cols; j++){
		des.at<float>(i*cols+j) = src.at<float>(i,j);
	    }
	}
    }
    MatrixXd cv2eigen(const Mat& cvMat){
	int rows = cvMat.rows;
	int cols = cvMat.cols;
	MatrixXd eigenMat(rows, cols);

	for(int i= 0; i<rows; i++){
	    for(int j=0; j<cols; ++j){
		eigenMat(i,j) = cvMat.at<float>(i,j);
	    }
	}
	return eigenMat;
    }

    Mat eigen2cv(const MatrixXd& eigenMat){
	int rows = eigenMat.rows();
	int cols = eigenMat.cols();
	Mat cvMat(rows, cols, CV_32F);

	for(int i= 0; i<rows; i++){
	    for(int j=0; j<cols; ++j){
		cvMat.at<float>(i,j)= eigenMat(i,j);
	    }
	}
	return cvMat;
    }

    MatrixXd AddOne(const MatrixXd &m){
	MatrixXd tmp(m.rows()+1,1);
	MatrixXd oneMat(1,1);
	oneMat.fill(1);
	tmp <<  oneMat , m;
	return tmp;
    }

    MatrixXd RemoveOne(const MatrixXd &m){
	return m.block(1,0,m.rows()-1, m.cols());
    }

    MatrixXd Sigmoid(const MatrixXd& v){
	MatrixXd output(v.rows(), v.cols());
	for(int i =0; i<v.rows(); i++){
	    for(int j=0; j<v.cols(); j++){
		output(i,j) = Sigmoid(v(i,j));
	    }
	}
	return output;
    }

    MatrixXd SigmoidGrad(const MatrixXd& v){
	MatrixXd output(v.rows(), v.cols());
	for(int i =0; i<v.rows(); i++){
	    for(int j=0; j<v.cols(); j++){
		output(i,j) = SigmoidGrad(v(i,j));
	    }
	}
	return output;
    }

    MatrixXd Log(const MatrixXd& v){
	MatrixXd output(v.rows(), v.cols());
	for(int i =0; i<v.rows(); i++){
	    for(int j=0; j<v.cols(); j++){
		output(i,j) = log(v(i,j));
	    }
	}
	return output;
    }

    double Sigmoid(double z){
	return 1.0/(1.0+exp(-z));
    }

    double SigmoidGrad(double z){
	double sig = Sigmoid(z);
	return sig*(1-sig);
    }

};


