
#include "AITraining.h"

using namespace Eigen;


AITraining::AITraining(){

}

AITraining::~AITraining(){

}

void AITraining::Test(){
	Eigen::MatrixXd X(382, 28);
	Eigen::VectorXd y(382);
	std::cout << "Reading !";
	Read_CSV(X, y, "D:/AIProject/Tests/gestures_file_trainning.csv");
	//std::cout << y;
	std::cout << "Training !";
	AITraining::TrainingValue training;

	pca(training, X , y);

	std::cout << "Writing !";
	Write_CSV(X, y, "D:/AIProject/Tests/testCsv.csv");
}

void AITraining::Read_CSV(Eigen::MatrixXd& X, Eigen::VectorXd& y, std::string filename){

	std::ifstream data(filename);
	if (!data.is_open()) {
		LOG("file cant open to read data ")
		return;
	}

	std::string line;
	int i = 0, j = 0;
	while (std::getline(data, line))
	{
		std::stringstream  lineStream(line);
		std::string        cell;
		j = 0;
		while (std::getline(lineStream, cell, ','))
		{
			// You have a cell!!!!
			if (j == 0){
				y(i) = std::stoi(cell);
			}
			else{
				X(i, j - 1) = std::stod(cell);
			}
			++j;
		}
		++i;
	}
	data.close();
}


void AITraining::Write_CSV(Eigen::MatrixXd& X, Eigen::VectorXd& y, std::string filename){
	std::ofstream fout(filename);
	if (!fout)
	{
		LOG("File Not Opened")
			return;
	}
	
	for (int i = 0; i < X.rows(); i++){
		fout << y(i) << ",";
		for (int j = 0; j < X.cols(); j++){
			fout << X(i, j) << ",";
		}
		fout << std::endl;
	}

	fout.close();
}

void AITraining::pca(AITraining::TrainingValue& training, MatrixXd& X, VectorXd& y, int numComponents){

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
	for (int i = 0; i < training.eigenVectors.cols(); ++i){// Orcer eigen vectors And select components
		newEigenVectors.col(i) = training.eigenVectors.col(collectionPairs[i].second);
	}
	training.eigenVectors.resize(training.eigenVectors.rows(), numComponents);
	training.eigenValues.resize(numComponents);

	//Select Components
}

bool comparatorPairEigenValue(const std::pair<double, int>& l,const std::pair<double, int>& r)
{
	return l.first > r.first;
}