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
#include <CinderOpenCV.h>
#include <fstream>

namespace fs = boost::filesystem;

class AIDataSet{
public:

    AIDataSet();
    AIDataSet(std::string,std::string);
    ~AIDataSet();
    
    AIStatus read_images(std::string);
    
    /**
        Save images to a file. Each image is contained in a row of the file
     */
	AIStatus save_images(std::string);
    
    /*
        Load csv file with the images previously saved
     */
    AIStatus load_data(std::string);
    
    void saveImage(int index,cv::Mat);
    void saveUser(int index,std::string);
    void saveToFile(std::string);

    
private:
    
    cv::CascadeClassifier       _classifier;
    
public:
    std::multimap<int,cv::Mat>  _images;
    
    std::map<int, std::string>  _usuarios;
    
};

#endif
