//
//  AITechnique.h
//  FaceRecognizer
//
//  Created by Efrain Astudillo on 1/18/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#ifndef FaceRecognizer_AITechnique_h
#define FaceRecognizer_AITechnique_h
#include "Eigen/Dense"
#include <iostream>
#include "AIUtil.h"

class _AITecnique{
public:
    virtual Eigen::MatrixXd _compute(const Eigen::MatrixXd& X, const Eigen::Matrix<int, Eigen::Dynamic, 1>& y) = 0;
    virtual void _extract() = 0;
};


class AIPca : public _AITecnique{
public:
    AIPca();
    
    Eigen::MatrixXd _compute(const Eigen::MatrixXd& X, const Eigen::Matrix<int, Eigen::Dynamic, 1>& y);
    void _extract();
    
};

class AILda : public _AITecnique{
public:
    AILda();
    
    Eigen::MatrixXd _compute(const Eigen::MatrixXd& X, const Eigen::Matrix<int, Eigen::Dynamic, 1>& y);
    void _extract();
    
};

#endif
