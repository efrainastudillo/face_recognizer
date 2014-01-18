//
//  AIDataSet.h
//  FaceRecognizer
//
//  Created by Efrain Astudillo on 1/6/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#ifndef FaceRecognizer_DataSet_h
#define FaceRecognizer_DataSet_h


#include "AIUtil.h"

#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <Eigen/Dense>
#include <boost/filesystem/operations.hpp>

namespace fs = boost::filesystem;

class AIDataSet{
public:
    
    
    Eigen::VectorXf ope;

    AIDataSet();
    AIDataSet(std::string,std::string);
    ~AIDataSet();
    
    AIStatus read_images(std::string);
    
    /*  Processing the image <bold>image</bold>, convert to gray-scale, find a face into it and extract the ROI
        then resize the image to normalize the same size all images
    */
    void processing_image(cv::Mat&);
    
    /**
        Save images to a file. Each image is contained in a row of the file
     */
	AIStatus save_images(std::string);
    
    /*
        Load csv file with the images previously saved
     */
    AIStatus load_data(std::string);
    void shuffle();
    
private:
    fs::path                    _path;
    cv::CascadeClassifier       _classifier;
    
public:
    std::multimap<int,cv::Mat>  _images;
    
    std::map<int, std::string>  _names;
    
};

#endif
