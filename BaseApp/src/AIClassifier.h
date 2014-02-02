//
//  _AIClassifier.h
//  FaceRecognizer
//
//  Created by Efrain Astudillo on 1/18/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#ifndef FaceRecognizer_AIClassifier_h
#define FaceRecognizer_AIClassifier_h

#include <iostream>
#include "Eigen/Dense"

#include "AIUtil.h"
#include "AIModel.h"
#include "AIDistance.h"
#include "AIFile.h"


// abstract class
class _AIClassifier{
public:

	//_AIClassifier():mDistance(NULL){};
    _AIClassifier(_AIDistance&);
	virtual AIModel::TrainingModel compute(const Eigen::MatrixXd& X, const AIModel::Eigen_VectorXx& y, const AIModel::TrainingValue& trainingValue) = 0;
    virtual AIModel::DataLabel predict(const Eigen::RowVectorXd& X) = 0;

	_AIDistance *mDistance;
};

class AINearestNeighbor : public _AIClassifier{
public:

    //AINearestNeighbor();
    AINearestNeighbor(_AIDistance&);
    
    AIModel::TrainingModel compute(const Eigen::MatrixXd& X, const AIModel::Eigen_VectorXx& y, const AIModel::TrainingValue& trainingValue);
    AIModel::DataLabel predict(const Eigen::RowVectorXd& X);
};

#endif
