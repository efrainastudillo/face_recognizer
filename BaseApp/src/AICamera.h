//
//  AICamera.h
//  BaseApp
//
//  Created by Efrain Astudillo on 1/24/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#ifndef BaseApp_AICamera_h
#define BaseApp_AICamera_h

#include "cinder/app/AppBasic.h"
#include "cinder/Capture.h"
#include "cinder/gl/Texture.h"

#include "AIDataSet.h"

using namespace ci;
using namespace ci::app;


class AICamera{
public:
    AICamera();
    ~AICamera(){}
    void initialize();
    AIStatus processing_image(cv::Mat&);
    void update();
    void draw(ci::Rectf bounds);
    AIDataSet& get_dataSet(){
        return this->mDataSet;
    };
    
    
    void enableTraining(bool);
    
    AIDataSet mDataSet;
    ci::Capture _capture;
    cv::CascadeClassifier       _classifier;
    gl::Texture _texture;
    gl::Texture _miniTexture;
    
    int mContador;
    int mContadorUsuario;
    double mSegundos;
    bool mIsTraining;
};

#endif
