#pragma once
#ifndef FaceRecognizer_AIFile_h
#define FaceRecognizer_AIFile_h

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "AIModel.h"
#include "Eigen/Dense"

using namespace Eigen;

// save model


inline void SaveMatrix(const Eigen::MatrixXd& X, std::string filename){
	std::ofstream fout(filename);
	if (!fout)
	{
		LOG("File Not Opened")
			return;
	}
	fout << X.rows() << "," << X.cols() << std::endl;
	for (int i = 0; i < X.rows(); ++i){
		for (int j = 0; j < X.cols(); ++j){
			fout << X(i, j) << ",";
		}
		fout << std::endl;
	}

	fout.close();
};

inline static void SaveVectorXx(const AIModel::Eigen_VectorXx& X, std::string filename){
	std::ofstream fout(filename);
	if (!fout)
	{
		LOG("File Not Opened")
			return;
	}
	fout << X.size() << std::endl;
	for (int i = 0; i < X.size(); i++){
		fout << X(i) << ",";
		fout << std::endl;
	}

	fout.close();
};
inline static void SaveProjections(const std::vector<Eigen::MatrixXd>& projections, std::string filename){
	std::ofstream fout(filename);
	if (!fout)
	{
		LOG("File Not Opened")
			return;
	}

	for (auto p = 0; p < projections.size(); ++p){
		const MatrixXd& X = projections[p];
		for (int i = 0; i < X.rows(); ++i){
			fout << p << "," << X.rows() << "," << X.cols() << ",";
			for (int j = 0; j < X.cols(); ++j){
				fout << X(i, j) << ",";
			}
			fout << std::endl;
		}
	}

	fout.close();
};


inline static void SAVE_AIMODEL(const AIModel::TrainingModel& trainingModel, std::string trainingPath){

	std::string filePath =trainingPath;

	std::string fileW(filePath + "W.csv");
	std::string fileY(filePath + "Y.csv");
	std::string fileMu(filePath + "mu.csv");
	std::string fileProjections(filePath + "projections.csv");

	SaveMatrix(trainingModel.W, fileW);
	SaveVectorXx(trainingModel.y, fileY);
	SaveMatrix(trainingModel.mu, fileMu);
	SaveProjections(trainingModel.projections, fileProjections);

};
//Read Model

inline static void ReadMatrix(Eigen::MatrixXd& X, std::string filename){
	std::ifstream data(filename);
	if (!data.is_open()) {
		LOG("file cant open to read data ")
			return;
	}

	std::string line;
	int i = 0, j = 0, rows = 0, cols = 0;
	while (std::getline(data, line))
	{
		std::stringstream  lineStream(line);
		std::string        cell;
		j = 0;
		while (std::getline(lineStream, cell, ','))
		{
			if (i == 0 && j == 0){
				rows = std::stoi(cell);			
			}
			else{
				if (i == 0 && j == 1){
					cols = std::stoi(cell);
					X = Eigen::MatrixXd(rows, cols);					
				}
				else{
					X(i - 1, j) = std::stod(cell);
				}
			}
						
			++j;
		}
		++i;
	}
	
	data.close();
};

inline static void ReadVectorXx(AIModel::Eigen_VectorXx& X, std::string filename){
	std::ifstream data(filename);
	if (!data.is_open()) {
		LOG("file cant open to read data ")
			return;
	}

	std::string line;
	int i = 0, j = 0, size = 0;
	while (std::getline(data, line))
	{
		std::stringstream  lineStream(line);
		std::string        cell;
		j = 0;
		while (std::getline(lineStream, cell, '\n'))
		{
			if (i == 0){
				size = std::stoi(cell);
				X = AIModel::Eigen_VectorXx(size);
			}
			else{
				X(i - 1) = std::stoi(cell);
			}
			++j;
		}
		++i;
	}
	data.close();
};

inline static void ReadProjections(std::vector<Eigen::MatrixXd>& projections, std::string filename){
	std::ifstream data(filename);
	if (!data.is_open()) {
		LOG("file cant open to read data ")
			return;
	}

	std::string line;
	int i = 0, j = 0, rows = 0, cols = 0, oldProjectionIdx = -1, projectIdx = -1;
	while (std::getline(data, line))
	{
		std::stringstream  lineStream(line);
		std::string        cell;
		j = 0;
		
		while (std::getline(lineStream, cell, ','))
		{
			// You have a cell!!!!
			if (j == 0){
				projectIdx = std::stoi(cell);
				
			}
			else{
				if (j == 1){
					rows = std::stoi(cell);

				}
				else{
					if (j == 2){
						cols = std::stoi(cell);
						if (oldProjectionIdx != projectIdx){
							projections.push_back(Eigen::MatrixXd(rows, cols));
							oldProjectionIdx = projectIdx;
						}

					}
					else{
						projections[projectIdx](i - projectIdx * rows, j - 3) = std::stod(cell);
					}
				}
				
			}
			
			++j;
		}
		++i;
	}
	data.close();
};



inline static void READ_AIMODEL(AIModel::TrainingModel& trainingModel, std::string trainingPath){
	std::string filePath = trainingPath;

	std::string fileW(filePath + "W.csv");
	std::string fileY(filePath + "Y.csv");
	std::string fileMu(filePath + "mu.csv");
	std::string fileProjections(filePath + "projections.csv");

	ReadMatrix(trainingModel.W, fileW);
	ReadVectorXx(trainingModel.y, fileY);
	MatrixXd muHelper;
	ReadMatrix(muHelper, fileMu);
	trainingModel.mu = muHelper.row(0);
	ReadProjections(trainingModel.projections, fileProjections);
};

#endif