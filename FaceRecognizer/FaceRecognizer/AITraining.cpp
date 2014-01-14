
#include "AITraining.h"

using namespace Eigen;

void Test(){
	
}

AITraining::TrainingValue& pca(AITraining::TrainingValue& training, MatrixXd& X, VectorXd& y, int numComponents = 0){

	int n = X.rows();
	int d = X.cols();

	if ((numComponents <= 0) || (numComponents > n))
		numComponents = n;

	//Calculate Mean
	training.mu = RowVectorXd::Zero(d);
	
	for (int i = 0; i < n; i++){
		training.mu = training.mu + X.row(i);
	}
	training.mu = training.mu / n;

	for (int i = 0; i < n; i++){
		X.row(i) = X.row(i) - training.mu;
	}
	// end calculate mean

	MatrixXd C;
	

	if (n > d){
		C = X.transpose() * X;		
		SelfAdjointEigenSolver<MatrixXd> eigensolver(C);
		//if (eigensolver.info() != Success) abort();
		training.eigenValues = eigensolver.eigenvalues();
		training.eigenVectors = eigensolver.eigenvectors();
	}
	else{
		C = X * X.transpose();
		SelfAdjointEigenSolver<MatrixXd> eigensolver(C);
		//if (eigensolver.info() != Success) abort();
		training.eigenValues = eigensolver.eigenvalues();
		training.eigenVectors = eigensolver.eigenvectors();

		training.eigenVectors = X.transpose() * training.eigenVectors;

		for (int i = 0; i < n; ++i){
			training.eigenVectors.col(i) = training.eigenVectors.col(i) / training.eigenVectors.col(i).norm();
		}
	}
		
	//Sorting by eigen values
		
	std::pair<double, int> pairEigenValue;

	std::vector<std::pair<double, int>> collectionPairs;
	for (int i = 0; i < training.eigenValues.size(); ++i){
		collectionPairs.push_back(std::pair<double, int>(training.eigenValues(i), i));
	}

	std::sort(collectionPairs.begin(), collectionPairs.end(), comparatorPairEigenValue);

	MatrixXd newEigenVectors(training.eigenVectors.rows(), training.eigenVectors.cols());
	for (int i = 0; i < numComponents; ++i){// Orcer eigen vectors And select components
		newEigenVectors.col(i) = training.eigenVectors.col(collectionPairs[i].second);
	}
	training.eigenVectors.resize(training.eigenVectors.rows(), numComponents);
	training.eigenValues.resize(numComponents);

	//Select Components
	

	return training;
}

bool comparatorPairEigenValue(const std::pair<double, int>& l,const std::pair<double, int>& r)
{
	return l.first > r.first;
}