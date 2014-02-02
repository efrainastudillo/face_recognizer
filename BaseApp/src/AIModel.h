#pragma once
#ifndef __BaseApp__AIModel__
#define __BaseApp__AIModel__

#include <string>
#include <vector>
#include "Eigen/Dense"

class AIModel{
public:

	typedef int DataLabel;
	typedef Eigen::Matrix<int, Eigen::Dynamic, 1>  Eigen_VectorXx;

	
	struct TrainingValue {
			Eigen::VectorXd eigenValues;
			Eigen::MatrixXd eigenVectors;
			Eigen::RowVectorXd mu;
		};

	struct TrainingModel{
			Eigen::MatrixXd W;
			Eigen_VectorXx y;
			Eigen::RowVectorXd mu;
			std::vector<Eigen::MatrixXd> projections;
		};
};

#endif /* defined(__BaseApp__AIModel__) */