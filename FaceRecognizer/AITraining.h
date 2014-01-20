#ifndef FaceRecognizer_AITraining_h
#define FaceRecognizer_AITraining_h

#include "AIUtil.h"

#include <iostream>
#include <fstream>
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
		typedef std::string DataLabel;
		typedef Eigen::Matrix<DataLabel, Eigen::Dynamic, 1>  Eigen_VectorXx;

		AITraining();
		~AITraining();

		void Test(std::string pathTraining);

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

		
		
		void Read_CSV(Eigen::MatrixXd& X, Eigen_VectorXx& y, std::string filename);

		void Write_CSV(const Eigen::MatrixXd& X, const Eigen_VectorXx& y, std::string filename);

		//Algorithms for AI technique

		
		// PCA
		void pca(AITraining::TrainingValue& training, const Eigen::MatrixXd& X, const Eigen_VectorXx& y, int numComponents = 0);

		//LDA

		void lda(AITraining::TrainingValue& training, const Eigen::MatrixXd& X, const Eigen_VectorXx& y, int numComponents = 0);
		void ldaOptimizedW(AITraining::TrainingValue& training, const Eigen::MatrixXd& X, const Eigen_VectorXx& y, int numComponents = 0);

		//General functions
		void project(Eigen::MatrixXd& projection, const Eigen::MatrixXd& W, const Eigen::MatrixXd& X, Eigen::RowVectorXd mu);
		void Train(AITraining::TrainingModel& trainingModel, const Eigen::MatrixXd& X, const Eigen_VectorXx& y, int AImethod = 0);
		DataLabel predict(const Eigen::RowVectorXd& X, AITraining::TrainingModel& trainingModel, int distanceType = 0);

		//Algorithms for Calculating Distance

		double EuclideanDistance(const Eigen::MatrixXd& P, const Eigen::MatrixXd& Q);
		double CosineDistance(const Eigen::MatrixXd& P, const Eigen::MatrixXd& Q);

		//Utilitie functions

		Eigen::RowVectorXd meanRow(const Eigen::MatrixXd& X);
		Eigen::MatrixXd MatrixMinusRowVector(const Eigen::MatrixXd& matrix, Eigen::RowVectorXd& rowVector);
		std::vector<DataLabel> uniqueFromVector(const Eigen_VectorXx& colVector);
		void ReplaceValue(Eigen::MatrixXd& matrix,double originalValue, double newValue);

		//Files for AI Models

		void SaveMatrix(const Eigen::MatrixXd& X, std::string filename);
		void SaveVectorXx(const Eigen_VectorXx& X, std::string filename);
		void SaveProjections(const std::vector<Eigen::MatrixXd>& projections, std::string filename);
		
		void SaveTrainingModel(const AITraining::TrainingModel& trainingModel, std::string trainingPath);

		void ReadMatrix(Eigen::MatrixXd& X, std::string filename);
		void ReadVectorXx(Eigen_VectorXx& X, std::string filename);
		void ReadProjections(std::vector<Eigen::MatrixXd>& projections, std::string filename);

		void ReadTrainingModel(AITraining::TrainingModel& trainingModel, std::string trainingPath);
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