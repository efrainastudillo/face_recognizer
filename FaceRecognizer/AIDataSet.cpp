//
//  DataSet.cpp
//  FaceRecognizer
//
//  Created by Efrain Astudillo on 1/6/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#include "AIDataSet.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/eigen.hpp>
#include <fstream>

AIDataSet::AIDataSet(){
    std::cout<<"Data Set..."<<std::endl;
    _path = fs::path("/Users/efrainastudillo/scikit_learn_data/");
    _classifier = cv::CascadeClassifier();
    _classifier.load("/Users/efrainastudillo/Documents/Development/opencv/data/haarcascades/haarcascade_frontalface_alt.xml");
    
    _images = cv::vector<cv::Mat>();
}

AIDataSet::AIDataSet(std::string image_path,std::string classifier_path){
    _path = fs::path(image_path);
    _classifier = cv::CascadeClassifier();
    _classifier.load(classifier_path);
    
    _images = cv::vector<cv::Mat>();
}

AIDataSet::~AIDataSet(){

}
/**
    Save images to a file. Each image is contained in a row of the file
 */
AIStatus AIDataSet::save_images(std::string filename){
    std::ofstream fout(filename);
    if(!fout)
    {
        LOG("File Not Opened")
        return AIStatus::AI_STATUS_ERROR;
    }
    if (_images.empty())
    {
        LOG("not found images to save")
        return AIStatus::AI_STATUS_NOT_IMAGES;
    }
    cv::vector<cv::Mat>::iterator iter = _images.begin();
    while (iter != _images.end())
    {
        if( (*iter).channels() == 1)
        {
            for(int i=0; i<(*iter).rows; i++)
            {
                for(int j=0; j<(*iter).cols; j++)
                {
                    unsigned int pixel = (*iter).at<uchar>(i,j);
                    fout<<pixel<<",";
                }
            }
        }
        iter++;
    }
    
    fout<<std::endl;
    fout.close();
    
    return AIStatus::AI_STATUS_OK;
}

AIStatus AIDataSet::load_data(){
    
    return AIStatus::AI_STATUS_OK;
}


//Processing the image <bold>image</bold>, convert to gray-scale, find a face into it and extract the ROI
//then resize the image to normalize the same size all images
void AIDataSet::processing_image(cv::Mat &image){
    //cv::Mat image = tmp.clone();
    //convert captured image to gray scale and equalize
    cv::cvtColor(image, image, CV_BGR2GRAY);
    cv::equalizeHist(image, image);
    
    //create a vector array to store the face found
    std::vector<cv::Rect> faces;
    
    //find faces and store them in the vector array
    _classifier.detectMultiScale(image, faces,1.1, 2, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));
    std::cout<<"Faces: "<<faces.size()<<std::endl;
    //extract roi containing the face if there more than one, only the first is keeping in memory
    //this can be manipulate capturing the image more accurate posible
    if(faces.size()>0){
        cv::Point pt1(faces[0].x, faces[0].y);
        cv::Point pt2(faces[0].x + faces[0].width, faces[0].y + faces[0].height);
        image=image(cv::Rect(pt1,pt2));
        
        //resize the image to 100X100 to obtain a vector of size equal 10000 to increase performance
        cv::resize(image, image, cv::Size(100,100));
    }
}

//Read the images from ode disk a pre-processing to save a file
//Each directory contains a set of images of each person
AIStatus AIDataSet::read_images(){
    
    fs::directory_iterator _end;
    
    //if this path is not correct or the path is correct but is not a directory
    if (!fs::exists(_path) || !fs::is_directory(_path)) {
        return AIStatus::AI_STATUS_ERROR;
    }
    
    std::cout<<"Directory exist..."<<std::endl;
    for (fs::directory_iterator _parent_dir(_path); _parent_dir != _end; _parent_dir++) {
        if (fs::is_directory(_parent_dir->status())) {
            for (fs::directory_iterator _children_dir(fs::path(_path / _parent_dir->path().stem()));
                _children_dir != _end; _children_dir ++) {
            
                //show whether is a file and not a directory
                if (fs::is_regular_file(_children_dir->status())) {
                    //std::cout<<"dir: "<<_children_dir->path().filename()<<std::endl;
                    cv::Mat imagen = cv::imread(_children_dir->path().string());
                    processing_image(imagen);
                    _images.push_back(imagen);
                }
            }
        }
    }

    return AIStatus::AI_STATUS_OK;
}

void AIDataSet::shuffle(){}