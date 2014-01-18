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


double AIEuclideanDistance::compute(cv::vector<int> &v1,cv::vector<int> &v2){
    
    return 0.0L;
}