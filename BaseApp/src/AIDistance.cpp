//
//  AIDistance.cpp
//  FaceRecognizer
//
//  Created by Efrain Astudillo on 1/18/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#include "AIDistance.h"


_AIDistance::_AIDistance(std::string name){
    _name = name;
}
std::string _AIDistance::get_name(){
    return _name;
}

// ==========================================================================

AIEuclideanDistance::AIEuclideanDistance():_AIDistance("Euclidean Distance"){
    // initialize instance concrete
}

double AIEuclideanDistance::compute(const Eigen::MatrixXd& P, const Eigen::MatrixXd& Q){
	return sqrt((P - Q).array().pow(2).sum());
}