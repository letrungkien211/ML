// My headers
#include "bpnn.hpp"
#include "utils.hpp"
#include "data.hpp"

/*************************************************/
#include <iostream>
#include <Eigen/Dense>
#include "cv.h"
#include "highgui.h"
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;
using namespace Eigen;
using namespace cv;
using namespace Utils;

int numData = 900;
int numTrain = 700;
int numTest = 200;
int numHidden = 30;
int maxIteration = 3000;
double learningRate = 0.2;
double lambda = 0.1;
double momentum = 0.5;
double threshold_ = 0.1;

int main(int argc, char **argv){
    MatrixXd data, label, 
	trainInput, trainLabel, trainOutput, 
	testInput, testLabel, testOutput,
	trainedTestLabel, trainedTestOutput;

    Mat cvTrainData, cvTrainLabel;
    string dataFileName("mnistdata.xml");
    string labelFileName("mnistlabel.xml");

    srand(time(NULL));
    BPNN bpnn(400,numHidden,10);

    cout << "Start Load" <<endl;
    Data::Load(dataFileName, labelFileName, cvTrainData, cvTrainLabel, numData);
    
    cout << "Start Convert" <<endl;
    data = cv2eigen(cvTrainData);

    label = cv2eigen(cvTrainLabel);
    LabelToMatrix(label, 10, trainOutput);

    cout << "Initialize " << endl;
    trainInput = data.block(0,0,numTrain,400);

    trainLabel = label.block(0,0,numTrain,1);
    LabelToMatrix(trainLabel, 10, trainOutput);

    testInput = data.block(numTrain,0,numTest,400);

    testLabel = label.block(numTrain,0,numTest,1);
    LabelToMatrix(testLabel,10, testOutput);

    cout << "Start train" <<endl;
    cout << trainInput.rows() << " " <<trainInput.cols() << endl;
    cout << trainOutput.rows() << " " <<trainOutput.cols() << endl;
    cout << label.rows() << " " <<label.cols() << endl;

    bpnn.SetWeight();
    bpnn = bpnn.Train(trainInput, trainOutput, learningRate, lambda, momentum,maxIteration, threshold_);

    bpnn.Predict(testInput, trainedTestOutput, trainedTestLabel);
    

    int cnt = 0;
    cout <<"TEst inut\n" << testInput <<endl;
    for(int i = 0; i < numTest; i++){
	cout << testLabel(i) << " " <<trainedTestLabel(i)<<endl;
	if(testLabel(i) == trainedTestLabel(i)){
	    cnt++;
	}
    }
    cout << " RATE : " << (double)cnt/numTest <<endl;
    
    return 0;
}



/*************************************************/





