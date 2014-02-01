//
//  AIClassifier.cpp
//  FaceRecognizer
//
//  Created by Efrain Astudillo on 1/18/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#include "AIClassifier.h"


AINearestNeighbor::AINearestNeighbor(){
    
}

bool AINearestNeighbor::compute(const Eigen::MatrixXd& X, const Eigen::Matrix<int, Eigen::Dynamic, 1>& y){
    return true;
}

void AINearestNeighbor::predict(){

}