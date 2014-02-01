//
//  AIBuilder.cpp
//  BaseApp
//
//  Created by Efrain Astudillo on 2/1/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#include "AIBuilder.h"

AIBuilder::AIBuilder(_AITecnique& tec, _AIClassifier& cla) : mTecnique(&tec),mClassifier(&cla){

}

void AIBuilder::compute(const Eigen::MatrixXd& X, const Eigen::Matrix<int, Eigen::Dynamic, 1>& y){}

void AIBuilder::predict(){}