#ifndef FaceRecognizer_AITraining_h
#define FaceRecognizer_AITraining_h

#include "AIUtil.h"

#include <iostream>
#include <opencv2/opencv.hpp>

#include <Eigen/Core>
#include <Eigen/Dense>
#include <vector>
#include <string>
#include <algorithm>    // std::sort

#include <boost/filesystem/operations.hpp>

namespace fs = boost::filesystem;

class AITraining{
	public:
		AITraining();
		~AITraining();

		void Test();

		struct TrainingValue {
			Eigen::VectorXd eigenValues;
			Eigen::MatrixXd eigenVectors;
			Eigen::RowVectorXd mu;
		};

		void pca(AITraining::TrainingValue& training, Eigen::MatrixXd& X, Eigen::VectorXd& y, int numComponents = 0);
		
		void Read_CSV(Eigen::MatrixXd& X, Eigen::VectorXd& y, std::string filename);

		void Write_CSV(Eigen::MatrixXd& X, Eigen::VectorXd& y, std::string filename);
		
};

#endif

bool comparatorPairEigenValue(const std::pair<double, int>& l, const std::pair<double, int>& r);