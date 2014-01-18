//
//  AIDistance.h
//  FaceRecognizer
//
//  Created by Efrain Astudillo on 1/18/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#ifndef FaceRecognizer_AIDistance_h
#define FaceRecognizer_AIDistance_h

#include<iostream>
#include <opencv2/opencv.hpp>

class _AIDistance{
private:
    std::string _name;
public:
    _AIDistance(std::string);
    // virtual function, make a class abstract
    virtual double compute() = 0;
    
    std::string get_name();
    
};

class AIEuclideanDistance : public _AIDistance{
public:
    AIEuclideanDistance();
    double compute(cv::vector<int>&,cv::vector<int>&);
};
#endif
