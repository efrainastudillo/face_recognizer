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
#include "AIModel.h"


// abstract class
class _AIClassifier{
public:
    virtual bool compute(const Eigen::MatrixXd& X, const AIModel::Eigen_VectorXx& y) = 0;
    virtual void predict() = 0;
};

class AINearestNeighbor : public _AIClassifier{
public:
    AINearestNeighbor();
    
    bool compute(const Eigen::MatrixXd& X, const AIModel::Eigen_VectorXx& y);
    void predict();
};

#endif
