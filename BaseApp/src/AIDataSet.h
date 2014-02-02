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
#include <fstream>

namespace fs = boost::filesystem;

class AIDataSet{
public:

    AIDataSet();
    ~AIDataSet();
    /*
    AIStatus read_images(std::string);
    
    
    //    Save images to a file. Each image is contained in a row of the file
     
	AIStatus save_images(std::string);
    
    
    //    Load csv file with the images previously saved
     
    AIStatus load_data(std::string);
    */
    void saveImage(int index,cv::Mat);
    void saveUser(int index,std::string nombre);
    void saveDataToFile(std::string filename);
    void saveNamesToFile(std::string filename);
    void loadDataFromFile(std::string filename);
    void loadNamesFromFile(std::string filename);
    
    int getLastIndex();
    
    void loadData();
    
    void clean(){
        _images.clear();
    };
    
    
    Eigen::MatrixXd data;
    Eigen::Matrix<int, Eigen::Dynamic, 1> labels;
    
private:
    
    cv::CascadeClassifier       _classifier;
    
public:
    std::multimap<int,cv::Mat>  _images;
    
    std::map<int, std::string>  _usuarios;
    
};

#endif
