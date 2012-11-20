#include "recognition.hpp"
void Recognition::Initialize(const MatrixXd & data, const MatrixXd &label,
		    int trainPortion, int crossVarlidationPortion,
		      int testPortion){
    int numData = data.rows();
    int b1,b2,b3;
    b1 = 0;
    b2 = trainPortion/10.0*numData;
    b3 = crossVarlidationPortion/10.0*numData;

    trainData = data.block(b1,0, b2, data.cols());
    crossVarlidationData = data.block(b2,0, b3, data.cols());
    testData = data.block(b3,0, numData-b3, data.cols());

    trainLabel = label.block(b1,0, b2, label.cols());
    crossVarlidationLabel = label.block(b2,0, b3, label.cols());
    testLabel = label.block(b3,0, numData-b3, label.cols());
    
}
void Recognition::Train(double learningRate, double lambda, double momentum){

}
void Recognition::CalculateCost(double &trainCost, double &crossVarlidattionCost, 
				double &testCost){

}

int main(int argc, char *argv[]){

}
