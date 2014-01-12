#ifndef FaceRecognizer_MainMethods_h
#define FaceRecognizer_MainMethods_h

#include <iostream>
#include <opencv2/opencv.hpp>

#include <Eigen/Dense>
#include "AIUtil.h"
#include <boost/filesystem/operations.hpp>

namespace fs = boost::filesystem;

class AIDataSet{
public:
	AIDataSet();
	AIDataSet(std::string, std::string);
	~AIDataSet();

	AIStatus read_images();
	void processing_image(cv::Mat&);
	AIStatus save_images(std::string);

	AIStatus load_data();
	void shuffle();

private:
	fs::path                _path;
	cv::CascadeClassifier   _classifier;
public:
	cv::vector<cv::Mat>     _images;
};

#endif