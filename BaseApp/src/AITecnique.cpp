//
//  AITecnique.cpp
//  FaceRecognizer
//
//  Created by Efrain Astudillo on 1/18/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#include "AITecnique.h"

using namespace Eigen;

AIPca::AIPca(){

}

AIModel::TrainingModel AIPca::_compute(const Eigen::MatrixXd& X, const AIModel::Eigen_VectorXx& y){
    AIModel::TrainingModel trainingModel;
	_AITecnique::TrainingValue training;

	pca(training, X, y, 0);

	trainingModel.W = training.eigenVectors;
	trainingModel.y = y;
	trainingModel.mu = training.mu;
	trainingModel.projections = std::vector<MatrixXd>();

	//MatrixXd projection(X.rows(), trainingModel.W.cols());
	MatrixXd projection;
	for (int i = 0; i < X.rows(); ++i){
		project(projection, trainingModel.W, X.row(i), trainingModel.mu);
		trainingModel.projections.push_back(projection);
	}

    return trainingModel;
}

void AIPca::_extract(){}
void pca(_AITecnique::TrainingValue& training, const Eigen::MatrixXd& X, const AIModel::Eigen_VectorXx& y, int numComponents){
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

	MatrixXd Xw = X;

	for (int i = 0; i < n; i++){
		Xw.row(i) = X.row(i) - training.mu;
	}
	// end calculate mean

	MatrixXd C;
	

	if (n > d){
		C = Xw.transpose() * Xw;		
		SelfAdjointEigenSolver<MatrixXd> eigensolver(C);
		//if (eigensolver.info() != Success) abort();
		training.eigenValues = eigensolver.eigenvalues();
		training.eigenVectors = eigensolver.eigenvectors();

	}
	else{
		C = Xw * Xw.transpose();
		SelfAdjointEigenSolver<MatrixXd> eigensolver(C);
		//if (eigensolver.info() != Success) abort();
		training.eigenValues = eigensolver.eigenvalues();
		training.eigenVectors = eigensolver.eigenvectors();

		training.eigenVectors = Xw.transpose() * training.eigenVectors;

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
	for (int i = 0; i < training.eigenVectors.cols(); ++i){// Orcer eigen vectors And select components
		newEigenVectors.col(i) = training.eigenVectors.col(collectionPairs[i].second);
		training.eigenValues(i) = collectionPairs[i].first;
	}
	
	training.eigenVectors = newEigenVectors;
	if (numComponents > training.eigenVectors.cols())
		numComponents = training.eigenVectors.cols();
	training.eigenVectors.conservativeResize(training.eigenVectors.rows(), numComponents);
	training.eigenValues.conservativeResize(numComponents);
}


AILda::AILda(){

}

AIModel::TrainingModel AILda::_compute(const Eigen::MatrixXd& X, const AIModel::Eigen_VectorXx& y){
    AIModel::TrainingModel trainingModel;
    
    _AITecnique::TrainingValue training;

	ldaOptimizedW(training, X, y, 0);

	trainingModel.W = training.eigenVectors;
	trainingModel.y = y;
	trainingModel.mu = training.mu;
	trainingModel.projections = std::vector<MatrixXd>();

	//MatrixXd projection(X.rows(), trainingModel.W.cols());
	MatrixXd projection;
	for (int i = 0; i < X.rows(); ++i){
		project(projection, trainingModel.W, X.row(i), trainingModel.mu);
		trainingModel.projections.push_back(projection);
	}
    
    return trainingModel;
}

void AILda::_extract(){}

void lda(_AITecnique::TrainingValue& training, const Eigen::MatrixXd& X, const AIModel::Eigen_VectorXx& y, int numComponents){
	
	int n = X.rows();
	int d = X.cols();
	
	//Get Number of unique values

	std::vector<AIModel::DataLabel> C = uniqueFromVector(y);
	
	if ((numComponents <= 0) || (numComponents >(C.size() - 1)))
		numComponents = C.size() - 1;

	//Calculate Mean
	RowVectorXd meanTotal = meanRow(X);
	// end mean
	
	//defining S matrixs
	MatrixXd Sw = MatrixXd::Zero(d, d), Sb = MatrixXd::Zero(d, d);

	for (auto i = 0; i < C.size(); ++i){
		
		//Extract Matrix of class Ci
		
		std::vector<int> indexClass;
		for (int k = 0; k < y.size(); ++k){
			if (C[i] == y(k)){
				indexClass.push_back(k);
			}
		}

		MatrixXd Xi(indexClass.size(), d);
		for (auto m = 0; m < indexClass.size(); ++m){
			Xi.row(m) = X.row(indexClass[m]);
		}
		
		//END Extract Matrix of class Ci

		//Calculating Sw and Sb
		RowVectorXd meanClass = meanRow(Xi);
		MatrixXd Xi_meanClass = MatrixMinusRowVector(Xi, meanClass);
		
		Sw += (Xi_meanClass.transpose() * Xi_meanClass);
		Sb += n * ((meanClass - meanTotal).transpose() * (meanClass - meanTotal));

		//std::cout << Sw.determinant() << " , " << (X.transpose() * X).determinant() << std::endl;
	}
	//Determinant
	std::cout << Sw.determinant() << std::endl;
	SelfAdjointEigenSolver<MatrixXd> eigensolver(Sw.inverse() * Sb);
	//if (eigensolver.info() != Success) abort();
	training.eigenValues = eigensolver.eigenvalues();
	training.eigenVectors = eigensolver.eigenvectors();
	
	
	//Sorting by eigen values

	std::pair<double, int> pairEigenValue;

	std::vector<std::pair<double, int>> collectionPairs;
	for (int i = 0; i < training.eigenValues.size(); ++i){
		collectionPairs.push_back(std::pair<double, int>(training.eigenValues(i), i));
	}

	std::sort(collectionPairs.begin(), collectionPairs.end(), comparatorPairEigenValue);

	MatrixXd newEigenVectors(training.eigenVectors.rows(), training.eigenVectors.cols());
	for (int i = 0; i < training.eigenVectors.cols(); ++i){// Orcer eigen vectors And select components
		newEigenVectors.col(i) = training.eigenVectors.col(collectionPairs[i].second);
		training.eigenValues(i) = collectionPairs[i].first;
	}

	training.eigenVectors = newEigenVectors;
	if (numComponents > training.eigenVectors.cols())
		numComponents = training.eigenVectors.cols();
	training.eigenVectors.conservativeResize(training.eigenVectors.rows(), numComponents);
	training.eigenValues.conservativeResize(numComponents);
}


void ldaOptimizedW(_AITecnique::TrainingValue& training, const Eigen::MatrixXd& X, const AIModel::Eigen_VectorXx& y, int numComponents){
	int n = X.rows();
	int d = X.cols();

	//Get Number of unique values

	int c = uniqueFromVector(y).size();

	_AITecnique::TrainingValue trainingPCA, trainingLDA;

	pca(trainingPCA, X, y, (n - c));

	

	MatrixXd projectionPCA_X;
	project(projectionPCA_X,trainingPCA.eigenVectors, X, trainingPCA.mu);	

	//Write_CSV(trainingPCA.eigenVectors, y, "D:/AIProject/Tests/matrixW.csv");

	lda(trainingLDA, projectionPCA_X, y, numComponents);

	

	training.eigenValues = trainingLDA.eigenValues;
	training.eigenVectors = trainingPCA.eigenVectors * trainingLDA.eigenVectors;
	training.mu = trainingPCA.mu;
}



void project(Eigen::MatrixXd& projection, const Eigen::MatrixXd& W, const Eigen::MatrixXd& X, Eigen::RowVectorXd mu){
	Eigen::MatrixXd Xw = X;
	for (int i = 0; i < X.rows(); i++){
		Xw.row(i) = X.row(i) - mu;
	}
	projection = Xw * W;
}

bool comparatorPairEigenValue(const std::pair<double, int>& l,const std::pair<double, int>& r){
	return l.first > r.first;
}



Eigen::MatrixXd MatrixMinusRowVector(const Eigen::MatrixXd& matrix, Eigen::RowVectorXd& rowVector){
	MatrixXd Xw(matrix.rows(), matrix.cols());

	for (int i = 0; i < matrix.rows(); i++){
		Xw.row(i) = matrix.row(i) - rowVector;
	}

	return Xw;
}

Eigen::RowVectorXd meanRow(const Eigen::MatrixXd& X){
	RowVectorXd totalMean = RowVectorXd::Zero(X.cols());
	for (int i = 0; i < X.rows(); i++){
		totalMean = totalMean + X.row(i);
	}
	totalMean = totalMean / X.rows();
	return totalMean;
}

std::vector<AIModel::DataLabel> uniqueFromVector(const AIModel::Eigen_VectorXx& colVector){
	std::vector<AIModel::DataLabel> C;

	for (int i = 0; i < colVector.size(); ++i){
		if (std::find(C.begin(), C.end(), colVector(i)) == C.end()){//no contains
			C.push_back(colVector(i));
		}
	}

	return C;
}