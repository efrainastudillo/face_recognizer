//
//  AIDataSet.cpp
//  FaceRecognizer
//
//  Created by Efrain Astudillo on 1/6/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#include "AIDataSet.h"


AIDataSet::AIDataSet(){
    
    LOG("My Image Path is: "<<__IMAGES_PATH__)
    LOG("My Classifier Path is: "<<__HAARCASCADE_PATH__)
    
    _names  = std::map<int, std::string>();
    _images = std::multimap<int,cv::Mat>();
}

AIDataSet::~AIDataSet(){

}

AIStatus AIDataSet::save_images(std::string filename){
    std::ofstream fout(filename);
    if(!fout)
    {
        LOG("File Not Opened")
        return AIStatus::AI_STATUS_ERROR;
    }
    if (_images.empty())
    {
        LOG("not found images to save, < _images std::map > is empty")
        return AIStatus::AI_STATUS_NOT_IMAGES;
    }
    std::multimap<int,cv::Mat>::iterator iter = _images.begin();
	//Writing 
	//Write ros and column in one line
	fout << _images.size() << "," << (_images.size() != 0 ? iter->second.rows * iter->second.cols : 0) << std::endl;
	//Write the matrix
    while (iter != _images.end())
    {
        if( iter->second.channels() == 1)
        {
            fout<<iter->first<<",";
            
            for(int i=0; i<iter->second.rows; i++)
            {
                for(int j=0; j<iter->second.cols; j++)
                {
                    unsigned int pixel = iter->second.at<uchar>(i,j);
					fout << pixel;
					//if (j != iter->second.cols - 1)
						fout << ",";
                }
            }
            fout<<std::endl;
        }
        iter++;
    }
    
    fout.close();
    
    //remove all data to free memory
    _images.clear();
    
    return AIStatus::AI_STATUS_OK;
}

AIStatus AIDataSet::load_data(std::string filename){
    std::ifstream data_images(filename);
    if (!data_images.is_open()) {
        LOG("file cant open to read data of the images")
        return AIStatus::AI_STATUS_CANT_OPEN_FILE;
    }
    
    std::string value;
    //std::istringstream line_stream;
    std::string pix;
    
    if (data_images.good())
    {
        while (std::getline(data_images,value,'\n'))
        {
            std::istringstream line_stream;
            line_stream.str(value);
            //LOG(value)      //debug print
        
            while (std::getline(line_stream, pix, ','))
            {
                //LOG(pix);    // to test whether is getting the pixel or not
                
                /* need to build a matrix or vector with Eigen or whathever you want*/
            }
            
        }
    
    }
    
    return AIStatus::AI_STATUS_OK;
}

void AIDataSet::processing_image(cv::Mat &image){
    //cv::Mat image = tmp.clone();
    //convert captured image to gray scale and equalize
    cv::cvtColor(image, image, CV_BGR2GRAY);
    cv::equalizeHist(image, image);
    
    //create a vector array to store the face found
    std::vector<cv::Rect> faces;
    
    //find faces and store them in the vector array
    _classifier.detectMultiScale(image, faces,1.1, 2, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));
    LOG("Faces detected: "<<faces.size())
    //extract roi containing the face if there more than one, only the first is keeping in memory
    //this can be manipulate capturing the image more accurate posible
    if(faces.size()>0){
        cv::Point pt1(faces[0].x, faces[0].y);
        cv::Point pt2(faces[0].x + faces[0].width, faces[0].y + faces[0].height);
        image=image(cv::Rect(pt1,pt2));
    }
    //resize the image to 100X100 to obtain a vector of size equal 10000 to increase performance
    cv::resize(image, image, cv::Size(100,100));
}

//Read the images from ode disk a pre-processing to save a file
//Each directory contains a set of images of each person
AIStatus AIDataSet::read_images(std::string){
    
    _path = fs::path(__IMAGES_PATH__);
    _classifier = cv::CascadeClassifier();
    
    if(!_classifier.load(__HAARCASCADE_PATH__))
    {
        LOG("haarcascade classifier file not found")
    }
    
    fs::directory_iterator _end;
    
    //if this path is not correct or the path is correct but is not a directory
    if (!fs::exists(_path) || !fs::is_directory(_path)) {
        return AIStatus::AI_STATUS_ERROR;
    }
    
    std::cout<<"Directory exist..."<<std::endl;
    
    //class identifier, link between index and name
    int class_code = 0;
    
    //this loop get the folder name of each person
    for (fs::directory_iterator _parent_dir(_path); _parent_dir != _end; _parent_dir++)
    {
        if (fs::is_directory(_parent_dir->status()))
        {
            //this loop get the filename of the each image into the folder
            for (fs::directory_iterator _children_dir(fs::path(_path / _parent_dir->path().stem()));
                _children_dir != _end; _children_dir ++)
            {
                                
                //show whether is a file and not a directory
                if (fs::is_regular_file(_children_dir->status()))
                {
                    //std::cout<<"dir: "<<_children_dir->path().filename()<<std::endl;
                    cv::Mat imagen = cv::imread(_children_dir->path().string());
                    processing_image(imagen);
                    _images.insert(std::make_pair(class_code, imagen));
                    
                }
            }
            _names.insert(std::make_pair(class_code, _parent_dir->path().filename().string()));
            class_code += 1;
        }
    }

    return AIStatus::AI_STATUS_OK;
}

void AIDataSet::shuffle(){}