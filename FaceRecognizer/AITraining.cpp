
#include "AITraining.h"

using namespace Eigen;


AITraining::AITraining(){

}

AITraining::~AITraining(){

}

void AITraining::Test(){
	Eigen::MatrixXd X(379, 15);//28
	Eigen::VectorXi y(379);

	Eigen::MatrixXd Xtest(379, 15);//28
	Eigen::VectorXi Ytest(379);




	

	int rowToPredict;

	std::cout << "Row to predict: ";
	std::cin >> rowToPredict;
	
	int technique;
	std::cout << "Technique: ";
	std::cin >> technique;

	std::cout << "Reading !";
	Read_CSV(X, y, "D:/AIProject/Tests/gestures_file_trainning.csv");
	Read_CSV(Xtest, Ytest, "D:/AIProject/Tests/gestures_file_test.csv");

	std::cout << "Training ! \n";
	AITraining::TrainingModel trainingModel;
	
	AITraining::Train(trainingModel, X, y, technique);
	//std::cout << trainingModel.W;
	int minClass = AITraining::predict(Xtest.row(rowToPredict), trainingModel,0);

	std::cout << "Prediction : " << minClass << std::endl;
	//std::cin.get();
	std::cout << "Writing ! \n";
	//Write_CSV(trainingModel.W, trainingModel.y, "D:/AIProject/Tests/matrixW.csv");
	std::cin.get();
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

void AITraining::Write_CSV(const Eigen::MatrixXd& X, const Eigen::VectorXi& y, std::string filename){
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


double AITraining::EuclideanDistance(const Eigen::MatrixXd& P, const Eigen::MatrixXd& Q){
	return sqrt((P - Q).array().pow(2).sum());
}
double AITraining::CosineDistance(const Eigen::MatrixXd& P, const Eigen::MatrixXd& Q){
	return  - (P * Q.transpose()).sum() / sqrt(((P.transpose() * P) *  (Q.transpose() * Q)).sum());	
}

int AITraining::predict(const Eigen::RowVectorXd& X, AITraining::TrainingModel& trainingModel, int distanceType){
	double minDist = std::numeric_limits<double>::max();
	int minClass = -1;

	MatrixXd Q;
	project(Q, trainingModel.W, X, trainingModel.mu);

	for (auto i = 0; i != trainingModel.projections.size(); ++i){
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

void AITraining::Train(AITraining::TrainingModel& trainingModel, const Eigen::MatrixXd& X, const Eigen::VectorXi& y, int AImethod){
	
	AITraining::TrainingValue training;

	switch (AImethod)
	{
	case 0:
		std::cout << "Using PCA..." << std::endl;
		pca(training, X, y);
		break;
	case 1:
		std::cout << "Using LDA..." << std::endl;
		ldaOptimizedW(training, X, y);
		break;
	default:
		std::cout << "Using PCA..." << std::endl;
		pca(training, X, y);
		break;
	}

	trainingModel.W = training.eigenVectors;
	trainingModel.y = y;
	trainingModel.mu = training.mu;
	trainingModel.projections = std::vector<MatrixXd>();

	//MatrixXd projection(X.rows(), trainingModel.W.cols());
	MatrixXd projection;
	for (int i = 0; i < X.rows(); ++i){
		project(projection, trainingModel.W, X.row(i), trainingModel.mu);
		trainingModel.projections.push_back(projection);
	}
	
}

void AITraining::lda(AITraining::TrainingValue& training, const Eigen::MatrixXd& X, const Eigen::VectorXi& y, int numComponents){
	
	int n = X.rows();
	int d = X.cols();
	
	//Get Number of unique values

	std::vector<double> C = uniqueFromVector(y);
	
	if ((numComponents <= 0) || (numComponents >(C.size() - 1)))
		numComponents = C.size() - 1;

	//Calculate Mean
	RowVectorXd meanTotal = meanRow(X);
	// end mean
	
	//defining S matrixs
	MatrixXd Sw = MatrixXd::Zero(d, d), Sb = MatrixXd::Zero(d, d);

	for (auto i = 0; i < C.size(); ++i){
		
		//Extract Matrix of class Ci
		
		std::vector<int> indexClass;
		for (int k = 0; k < y.size(); ++k){
			if (C[i] == y(k)){
				indexClass.push_back(k);
			}
		}

		MatrixXd Xi(indexClass.size(), d);
		for (auto m = 0; m < indexClass.size(); ++m){
			Xi.row(m) = X.row(indexClass[m]);
		}
		
		//END Extract Matrix of class Ci

		//Calculating Sw and Sb
		RowVectorXd meanClass = meanRow(Xi);
		MatrixXd Xi_meanClass = MatrixMinusRowVector(Xi, meanClass);
		
		Sw += (Xi_meanClass.transpose() * Xi_meanClass);
		Sb += n * ((meanClass - meanTotal).transpose() * (meanClass - meanTotal));

		//std::cout << Sw.determinant() << " , " << (X.transpose() * X).determinant() << std::endl;
	}
	
	SelfAdjointEigenSolver<MatrixXd> eigensolver(Sw.inverse() * Sb);
	//if (eigensolver.info() != Success) abort();
	training.eigenValues = eigensolver.eigenvalues();
	training.eigenVectors = eigensolver.eigenvectors();
	
	
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

void AITraining::ldaOptimizedW(AITraining::TrainingValue& training, const Eigen::MatrixXd& X, const Eigen::VectorXi& y, int numComponents){
	int n = X.rows();
	int d = X.cols();

	//Get Number of unique values

	int c = uniqueFromVector(y).size();

	AITraining::TrainingValue trainingPCA, trainingLDA;

	pca(trainingPCA, X, y, (n - c));

	

	MatrixXd projectionPCA_X;
	project(projectionPCA_X,trainingPCA.eigenVectors, X, trainingPCA.mu);	

	//Write_CSV(trainingPCA.eigenVectors, y, "D:/AIProject/Tests/matrixW.csv");

	lda(trainingLDA, projectionPCA_X, y, numComponents);

	

	training.eigenValues = trainingLDA.eigenValues;
	training.eigenVectors = trainingPCA.eigenVectors * trainingLDA.eigenVectors;
	training.mu = trainingPCA.mu;
}

Eigen::MatrixXd AITraining::MatrixMinusRowVector(const Eigen::MatrixXd& matrix, Eigen::RowVectorXd& rowVector){
	MatrixXd Xw(matrix.rows(), matrix.cols());

	for (int i = 0; i < matrix.rows(); i++){
		Xw.row(i) = matrix.row(i) - rowVector;
	}

	return Xw;
}

Eigen::RowVectorXd AITraining::meanRow(const Eigen::MatrixXd& X){
	RowVectorXd totalMean = RowVectorXd::Zero(X.cols());
	for (int i = 0; i < X.rows(); i++){
		totalMean = totalMean + X.row(i);
	}
	totalMean = totalMean / X.rows();
	return totalMean;
}

std::vector<double> AITraining::uniqueFromVector(const Eigen::VectorXi& colVector){
	std::vector<double> C;

	for (int i = 0; i < colVector.size(); ++i){
		if (std::find(C.begin(), C.end(), colVector(i)) == C.end()){//no contains
			C.push_back(colVector(i));
		}
	}

	return C;
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
	Write_CSV(training.eigenVectors, y, "D:/AIProject/Tests/eigenVectors.csv");

	
}

void AITraining::project(Eigen::MatrixXd& projection, const Eigen::MatrixXd& W, const Eigen::MatrixXd& X, Eigen::RowVectorXd mu){
	Eigen::MatrixXd Xw = X;
	for (int i = 0; i < X.rows(); i++){
		Xw.row(i) = X.row(i) - mu;
	}
	projection = Xw * W;
}


void AITraining::ReplaceValue(Eigen::MatrixXd& matrix, double originalValue, double newValue){
	for (int i = 0; i < matrix.rows(); ++i){
		for (int j = 0; j < matrix.cols(); ++j){
			if (matrix(i, j) == originalValue)
				matrix(i, j) = newValue;
		}
	}
}

bool comparatorPairEigenValue(const std::pair<double, int>& l,const std::pair<double, int>& r)
{
	return l.first > r.first;
}