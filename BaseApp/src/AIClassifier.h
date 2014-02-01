//
//  _AIClassifier.h
//  FaceRecognizer
//
//  Created by Efrain Astudillo on 1/18/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#ifndef FaceRecognizer_AIClassifier_h
#define FaceRecognizer_AIClassifier_h

#include <iostream>
#include "Eigen/Dense"


// abstract class
class _AIClassifier{
public:
    virtual bool compute(const Eigen::MatrixXd& X, const Eigen::Matrix<int, Eigen::Dynamic, 1>& y) = 0;
    virtual void predict() = 0;
};

class AINearestNeighbor : public _AIClassifier{
public:
    AINearestNeighbor();
    
    bool compute(const Eigen::MatrixXd& X, const Eigen::Matrix<int, Eigen::Dynamic, 1>& y);
    void predict();
};

#endif
