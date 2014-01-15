
#include "AITraining.h"

using namespace Eigen;


AITraining::AITraining(){

}

AITraining::~AITraining(){

}

void AITraining::Test(){
	Eigen::MatrixXd X(379, 28);
	Eigen::VectorXi y(379);

	Eigen::MatrixXd Xtest(379, 28);
	Eigen::VectorXi Ytest(379);

	std::cout << "Reading !";
	Read_CSV(X, y, "D:/AIProject/Tests/gestures_file_trainning.csv");
	Read_CSV(Xtest, Ytest, "D:/AIProject/Tests/gestures_file_test.csv");
	
	std::cout << "Training ! \n";
	AITraining::TrainingModel trainingModel;
	
	AITraining::Train(trainingModel, X, y);
	//std::cout << trainingModel.W;
	int minClass = AITraining::predict(Xtest.row(0), trainingModel, 0);

	std::cout << "Prediction : " << minClass << std::endl;
	//std::cin.get();
	std::cout << "Writing ! \n";
	Write_CSV(trainingModel.W, trainingModel.y, "D:/AIProject/Tests/matrixW.csv");
}

void AITraining::Read_CSV(Eigen::MatrixXd& X, Eigen::VectorXi& y, std::string filename){

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

void AITraining::Write_CSV(Eigen::MatrixXd& X, Eigen::VectorXi& y, std::string filename){
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


double AITraining::EuclideanDistance(const Eigen::RowVectorXd& P, const Eigen::RowVectorXd& Q){
	return sqrt((P - Q).array().pow(2).sum());
}
double AITraining::CosineDistance(const Eigen::RowVectorXd& P, const Eigen::RowVectorXd& Q){
	return  - (P * Q.transpose()).sum() / sqrt(((P.transpose() * P) *  (Q.transpose() * Q)).sum());	
}

int AITraining::predict(const Eigen::RowVectorXd& X, AITraining::TrainingModel& trainingModel, int distanceType){
	double minDist = std::numeric_limits<double>::max();
	int minClass = -1;

	RowVectorXd Q;
	project(Q, trainingModel.W, X, trainingModel.mu);

	for (std::vector<RowVectorXd>::size_type i = 0; i != trainingModel.projections.size(); ++i){
		double dist;

		switch (distanceType){
		case 0:
			dist = EuclideanDistance(trainingModel.projections[i], Q);
			break;
		case 1:
			dist = CosineDistance(trainingModel.projections[i], Q);
			break;
		default:
			dist = 0;
			break;
		}
			
		if (dist < minDist){
			minDist = dist;
			minClass = trainingModel.y(i);
		}
	}
	return minClass;
}

void AITraining::Train(AITraining::TrainingModel& trainingModel, const Eigen::MatrixXd& X, const Eigen::VectorXi& y){
	
	AITraining::TrainingValue training;
	pca(training, X, y);

	trainingModel.W = training.eigenVectors;
	trainingModel.y = y;
	trainingModel.mu = training.mu;
	trainingModel.projections = std::vector<RowVectorXd>();

	RowVectorXd projection(X.cols());
	for (int i = 0; i < X.rows(); ++i){
		project(projection, trainingModel.W, X.row(i), trainingModel.mu);
		trainingModel.projections.push_back(projection);
	}
	
}

void AITraining::lda(AITraining::TrainingValue& training, const MatrixXd& X, const VectorXi& y, int numComponents){

	int n = X.rows();
	int d = X.cols();

	//Get Number of unique values

	std::vector<double> C;

	for (int i = 0; i < y.size(); ++i){
		if (std::find(C .begin(), C.end(), y(i)) == C.end()){//no contains
			C.push_back(y(i));
		}
	}
	
	if ((numComponents <= 0) || (numComponents >(C.size() - 1)))
		numComponents = C.size() - 1;

	//Calculate Mean
	RowVectorXd totalMean = RowVectorXd::Zero(d);

	for (int i = 0; i < n; i++){
		totalMean = totalMean + X.row(i);
	}
	totalMean = totalMean / n;
	// end mean

	//defining S matrixs
	MatrixXd Sw(d, d), Sb(d, d);

	for (auto i = 0; i < C.size(); ++i){
		
		//Extract Matrix of class Ci
		
		std::vector<int> indexClass;
		for (int k = 0; k < y.size(); ++k){
			if (C[i] == y(k)){
				indexClass.push_back(k);
			}
		}

		MatrixXd Xi(indexClass.size(), d);
		for (auto m = 0; m < indexClass.size(); ++i){
			Xi.row(m) = X.row(indexClass[m]);
		}

		//END Extract Matrix of class Ci

		RowVectorXd meanClass = meanRow(Xi);

		
	}

	






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
	//std::cout << training.eigenValues;
	//Select Components	
	//VectorXi Y = y;
	//Write_CSV(training.eigenVectors, Y, "D:/AIProject/Tests/eigenVectors.csv");


}

Eigen::RowVectorXd AITraining::meanRow(const Eigen::MatrixXd& X){
	RowVectorXd totalMean = RowVectorXd::Zero(X.cols());
	for (int i = 0; i < X.rows(); i++){
		totalMean = totalMean + X.row(i);
	}
	totalMean = totalMean / X.rows();
	return totalMean;
}

void AITraining::pca(AITraining::TrainingValue& training, const MatrixXd& X, const VectorXi& y, int numComponents){

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
	//std::cout << training.eigenValues;
	//Select Components	
	//VectorXi Y = y;
	//Write_CSV(training.eigenVectors, Y, "D:/AIProject/Tests/eigenVectors.csv");

	
}

void AITraining::project(Eigen::RowVectorXd& projection, const Eigen::MatrixXd& W, const Eigen::MatrixXd& X, Eigen::RowVectorXd mu){
	Eigen::MatrixXd Xw = X;
	for (int i = 0; i < X.rows(); i++){
		Xw.row(i) = X.row(i) - mu;
	}
	projection = Xw * W;
}


bool comparatorPairEigenValue(const std::pair<double, int>& l,const std::pair<double, int>& r)
{
	return l.first > r.first;
}