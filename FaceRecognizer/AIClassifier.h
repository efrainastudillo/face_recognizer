//
//  _AIClassifier.h
//  FaceRecognizer
//
//  Created by Efrain Astudillo on 1/18/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#ifndef FaceRecognizer_AIClassifier_h
#define FaceRecognizer_AIClassifier_h

#include<opencv2/opencv.hpp>


// abstract class
class _AIClassifier{
public:
    virtual void compute() = 0;
    virtual void predict() = 0;
};

class AINearestNeighbor : public _AIClassifier{
public:
    AINearestNeighbor();
    
    void compute();
    void predict();
};

#endif
