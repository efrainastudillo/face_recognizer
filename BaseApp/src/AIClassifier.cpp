//
//  AIClassifier.cpp
//  FaceRecognizer
//
//  Created by Efrain Astudillo on 1/18/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#include "AIClassifier.h"
using namespace Eigen;


_AIClassifier::_AIClassifier(_AIDistance& dist) : mDistance(&dist){
	
}

AINearestNeighbor::AINearestNeighbor(_AIDistance& dist) : _AIClassifier(dist){

}

AIModel::TrainingModel AINearestNeighbor::compute(const Eigen::MatrixXd& X, const AIModel::Eigen_VectorXx& y, const AIModel::TrainingValue& trainingValue){

	AIModel::TrainingModel trainingModel;

	trainingModel.W = trainingValue.eigenVectors;
	trainingModel.y = y;
	trainingModel.mu = trainingValue.mu;
	trainingModel.projections = std::vector<MatrixXd>();

	//MatrixXd projection(X.rows(), trainingModel.W.cols());
	MatrixXd projection;
	for (int i = 0; i < X.rows(); ++i){
		project(projection, trainingModel.W, X.row(i), trainingModel.mu);
		trainingModel.projections.push_back(projection);
	}

    return trainingModel;
}


AIModel::DataLabel AINearestNeighbor::predict(const Eigen::RowVectorXd& X){
	AIModel::TrainingModel trainingModel;

	READ_AIMODEL(trainingModel, __TRAINING_PATH__);

	double minDist = std::numeric_limits<double>::max();
	//AIModel::DataLabel minClass = "None";
	AIModel::DataLabel minClass = -1;

	MatrixXd Q;
	project(Q, trainingModel.W, X, trainingModel.mu);

	for (auto i = 0; i != trainingModel.projections.size(); ++i){
		double dist = mDistance->compute(trainingModel.projections[i], Q);
		if (dist < minDist){
			minDist = dist;
			minClass = trainingModel.y(i);
		}
	}
	return minClass;
}