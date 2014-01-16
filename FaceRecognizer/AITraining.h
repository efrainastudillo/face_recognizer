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
#include <limits>
#include <math.h> 

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

		struct TrainingModel{
			Eigen::MatrixXd W;
			Eigen::VectorXi y;
			Eigen::RowVectorXd mu;
			std::vector<Eigen::MatrixXd> projections;
		};

		
		
		void Read_CSV(Eigen::MatrixXd& X, Eigen::VectorXi& y, std::string filename);

		void Write_CSV(const Eigen::MatrixXd& X, const Eigen::VectorXi& y, std::string filename);

		//Algorithms for AI technique

		
		// PCA
		void AITraining::pca(AITraining::TrainingValue& training, const Eigen::MatrixXd& X, const Eigen::VectorXi& y, int numComponents = 0);

		//LDA

		void AITraining::lda(AITraining::TrainingValue& training, const Eigen::MatrixXd& X, const Eigen::VectorXi& y, int numComponents = 0);
		void AITraining::ldaOptimizedW(AITraining::TrainingValue& training, const Eigen::MatrixXd& X, const Eigen::VectorXi& y, int numComponents = 0);

		//General functions
		void AITraining::project(Eigen::MatrixXd& projection, const Eigen::MatrixXd& W, const Eigen::MatrixXd& X, Eigen::RowVectorXd mu);
		void AITraining::Train(AITraining::TrainingModel& trainingModel, const Eigen::MatrixXd& X, const Eigen::VectorXi& y, int AImethod = 0);
		int AITraining::predict(const Eigen::RowVectorXd& X, AITraining::TrainingModel& trainingModel, int distanceType = 0);

		//Algorithms for Calculating Distance

		double AITraining::EuclideanDistance(const Eigen::MatrixXd& P, const Eigen::MatrixXd& Q);
		double AITraining::CosineDistance(const Eigen::MatrixXd& P, const Eigen::MatrixXd& Q);

		//Utilitie functions

		Eigen::RowVectorXd AITraining::meanRow(const Eigen::MatrixXd& X);
		Eigen::MatrixXd AITraining::MatrixMinusRowVector(const Eigen::MatrixXd& matrix, Eigen::RowVectorXd& rowVector);
		std::vector<double> AITraining::uniqueFromVector(const Eigen::VectorXi& colVector);
		void AITraining::ReplaceValue(Eigen::MatrixXd& matrix,double originalValue, double newValue);
		
};

#endif

bool comparatorPairEigenValue(const std::pair<double, int>& l, const std::pair<double, int>& r);
//
//#include <tr1/functional>
//
//class GameCharacter;
//int defaultHealthCalc(const GameCharacter& gc);
//
//class GameCharacter
//{
//public:
//	typedef std::tr1::function<int(const GameCharacter&)> HealthCalcFunc;
//
//	explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc)
//		: healthFunc(hcf)
//	{ }
//
//	int healthValue() const { return healthFunc(*this); }
//
//private:
//	HealthCalcFunc healthFunc;
//};