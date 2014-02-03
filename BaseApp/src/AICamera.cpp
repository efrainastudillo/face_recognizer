//
//  AICamera.cpp
//  BaseApp
//
//  Created by Efrain Astudillo on 1/24/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#include "AICamera.h"

AICamera::AICamera(){
}

void AICamera::initialize(){
    mDataSet.loadDataFromFile(__TRAINING_PATH__);
    mDataSet.loadNamesFromFile(__TRAINING_NAMES_PATH__);
    
    //===============     Artificial Intelligence       ================//
    mLda = AILda();
    mED = AIEuclideanDistance();
    mNN = AINearestNeighbor(mED);
    mBuilder = AIBuilder(mLda, mNN);
    
    
    //initilialize training
    mSaved = false;
    mIsPredicting = false;
    mIsTraining = false;
    mPredicted = false;
    mContador = 0;
    mSegundos = 0;
    mContadorUsuario = mDataSet.getLastIndex();
    
    try {
        _capture = ci::Capture(640,480);
        _capture.start();
        
        _classifier = cv::CascadeClassifier();
        
        if(!_classifier.load(__HAARCASCADE_PATH__))
        {
            LOG("haarcascade classifier file not found")
        }

        ci::app::console()<< "Camera initialized succesfully"<<std::endl;
    } catch (...) {
        ci::app::console()<< "Could not initialize camera"<<std::endl;
    }
}
void AICamera::draw(ci::Rectf bounds){
    if (_texture) {
        gl::draw(_texture,bounds);
    }
    
    if (_miniTexture) {
        ci::Rectf m(bounds.x1 + 10,bounds.y1 + 10 ,bounds.x1 + 90,bounds.y1 + 100);
        gl::draw(_miniTexture,m);
    }
}

AIStatus AICamera::processing_image(cv::Mat &img){
    cv::Mat tempImg = img.clone();
     //convert captured image to gray scale and equalize
     if (tempImg.data == NULL) {
         LOG("Image not Found")
         return AI_STATUS_ERROR;
     }
    if(tempImg.channels() > 1)
        cv::cvtColor(tempImg, tempImg, CV_BGR2GRAY);
     cv::equalizeHist(tempImg, tempImg);
    
     //create a vector array to store the face found
     std::vector<cv::Rect> faces;
     
     //find faces and store them in the vector array
     _classifier.detectMultiScale(tempImg, faces,1.1, 2, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE, cv::Size(150, 160));
    cv::Mat roi;
     //extract roi containing the face if there more than one, only the first is keeping in memory
     //this can be manipulate capturing the image more accurate posible
     if( faces.size()>0 && faces[0].x >= 0 && faces[0].y>=0 && faces[0].width<tempImg.cols && faces[0].height < tempImg.rows){
         cv::Point pt1(faces[0].x, faces[0].y);
         cv::Point pt2(faces[0].x + faces[0].width, faces[0].y + faces[0].height);
         roi=tempImg(cv::Rect(pt1,pt2));
     }else{
         return AIStatus::AI_STATUS_FACE_NOT_FOUND;
     }
    LOG("Faces detected: "<<faces.size())
     //resize the image to 100X100 to obtain a vector of size equal 10000 to increase performance
     cv::resize(roi, img, cv::Size(80,80));
    
    return AIStatus::AI_STATUS_OK;
}
void AICamera::update(){
    if (_capture) {
        if(_capture.checkNewFrame())
        {
            _texture = gl::Texture(_capture.getSurface());
            if (mIsTraining)
            {   enablePredicting(false);
                cv::Mat img(toOcv(_capture.getSurface()));
                AIStatus sTemp= processing_image(img);
                if (sTemp == AI_STATUS_OK)
                {
                    //para mostrar el el mini-rostro en la parte superior izquierda, encima de la imagen
                    _miniTexture = gl::Texture(fromOcv(img));
                    
                    //si el contador no ha llegado a 10?
                    if(mContador < 10 && getElapsedSeconds() - mSegundos > 2)
                    {
                        console() << "segundos elapsed: "<<getElapsedSeconds()<<std::endl;
                        // grabar imagen
                        mDataSet.saveImage(mContadorUsuario, img);
                        //
                        mContador ++; // contador de las 10 imagenes que nos serviran par el entrenamiento
                        mSegundos = getElapsedSeconds();
                    }else if ( mContador == 10)
                    {
                        mDataSet.saveUser(mContadorUsuario, mNombreUser);
                        mContador = 0;
                        mContadorUsuario = mContadorUsuario + 1;
                        mSaved = true;
                        mIsTraining = false;
                    }
                }
            }
            
            if (mIsPredicting) {
                enableTraining(false);
                int claseUsuario;
                cv::Mat img(toOcv(_capture.getSurface()));
                cv::cvtColor(img, img, CV_8UC1);
                AIStatus sTemp= processing_image(img);
                if (sTemp == AI_STATUS_OK)
                {
                    //para mostrar el el mini-rostro en la parte superior izquierda, encima de la imagen
                    _miniTexture = gl::Texture(fromOcv(img));
                    
                    Eigen::RowVectorXd tImagen(img.cols*img.rows);
                    CV2EIGEN(img, tImagen);
                    claseUsuario =  mBuilder.predict(tImagen);
                    mNombreUser = mDataSet.getNameById(claseUsuario);
                    LOG(claseUsuario)
                        //mSegundos = getElapsedSeconds();
                    mPredicted = true;
                }
                enablePredicting(false);
            }
        }
    }
}

void AICamera::enablePredicting(bool enable){
    mIsPredicting = enable;
}

void AICamera::enableTraining(bool enable){
    mIsTraining = enable;
}