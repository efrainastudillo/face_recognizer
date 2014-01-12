//
//  DataSet.h
//  FaceRecognizer
//
//  Created by Efrain Astudillo on 1/6/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#ifndef FaceRecognizer_DataSet_h
#define FaceRecognizer_DataSet_h

#include <iostream>
#include <opencv2/opencv.hpp>

#include <Eigen/Dense>
#include "AIUtil.h"
#include <boost/filesystem/operations.hpp>

namespace fs = boost::filesystem;

class AIDataSet{
public:
    AIDataSet();
    AIDataSet(std::string,std::string);
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
