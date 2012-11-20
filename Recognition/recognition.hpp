#ifndef RECOGNITION_HPP
#define RECOGNITION_HPP

#include <Eigen/Dense>
#include "../BPNN/bpnn.hpp"

using namespace std;
using namespace Eigen;

class Recognition:public BPNN{
private:
    MatrixXd trainData;
    MatrixXd trainLabel;
    MatrixXd crossVarlidationData;
    MatrixXd crossVarlidationLabel;
    MatrixXd testData;
    MatrixXd testLabel;
public:
    void Initialize(const MatrixXd & data, const MatrixXd &label,
		    int trainPortion, int crossVarlidationPortion,
		    int testPortion);
    void Train(double learningRate, double lambda, double momentum);
    void CalculateCost(double &trainCost, double &crossVarlidattionCost, 
		       double &testCost);
};


#endif
