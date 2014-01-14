#ifndef FaceRecognizer_AITraining_h
#define FaceRecognizer_AITraining_h


#include <iostream>
#include <opencv2/opencv.hpp>

#include <Eigen/Core>
#include <Eigen/Dense>
#include <algorithm>    // std::sort
#include <boost/filesystem/operations.hpp>

namespace fs = boost::filesystem;

class AITraining{
	public:
		AITraining();
		~AITraining();

		void Test();

		struct TrainingValue {
			Eigen::VectorXd& eigenValues;
			Eigen::MatrixXd& eigenVectors;
			Eigen::RowVectorXd& mu;
		};

		TrainingValue& pca(TrainingValue& training, Eigen::MatrixXd& X, Eigen::VectorXd& y, int numComponents = 0);
		

		
};

#endif

bool comparatorPairEigenValue(const std::pair<double, int>& l, const std::pair<double, int>& r);