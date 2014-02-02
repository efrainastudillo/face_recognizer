//
//  AITechnique.h
//  FaceRecognizer
//
//  Created by Efrain Astudillo on 1/18/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#ifndef FaceRecognizer_AITechnique_h
#define FaceRecognizer_AITechnique_h
// "Eigen/Dense"
#include <iostream>

#include <Eigen/Core>
#include <Eigen/Dense>
#include <vector>
#include <string>
#include <algorithm>    // std::sort
#include <limits>
#include <math.h> 

#include "AIUtil.h"
#include "AIModel.h"

class _AITecnique{
public:

	struct TrainingValue {
			Eigen::VectorXd eigenValues;
			Eigen::MatrixXd eigenVectors;
			Eigen::RowVectorXd mu;
		};

    virtual AIModel::TrainingModel _compute(const Eigen::MatrixXd& X, const AIModel::Eigen_VectorXx& y) = 0;
    virtual void _extract() = 0;
};


class AIPca : public _AITecnique{
public:
    AIPca();
    
    AIModel::TrainingModel _compute(const Eigen::MatrixXd& X, const AIModel::Eigen_VectorXx& y);
    void _extract();
	void pca(_AITecnique::TrainingValue& training, const Eigen::MatrixXd& X, const AIModel::Eigen_VectorXx& y, int numComponents);
    
};

class AILda : public _AITecnique{
public:
    AILda();
    
    AIModel::TrainingModel _compute(const Eigen::MatrixXd& X, const AIModel::Eigen_VectorXx& y);
    void _extract();
	void lda(_AITecnique::TrainingValue& training, const Eigen::MatrixXd& X, const AIModel::Eigen_VectorXx& y, int numComponents);
	void ldaOptimizedW(_AITecnique::TrainingValue& training, const Eigen::MatrixXd& X, const AIModel::Eigen_VectorXx& y, int numComponents);
    
};


Eigen::RowVectorXd meanRow(const Eigen::MatrixXd& X);
Eigen::MatrixXd MatrixMinusRowVector(const Eigen::MatrixXd& matrix, Eigen::RowVectorXd& rowVector);
std::vector<AIModel::DataLabel> uniqueFromVector(const AIModel::Eigen_VectorXx& colVector);

void project(Eigen::MatrixXd& projection, const Eigen::MatrixXd& W, const Eigen::MatrixXd& X, Eigen::RowVectorXd mu);
bool comparatorPairEigenValue(const std::pair<double, int>& l, const std::pair<double, int>& r);

#endif
