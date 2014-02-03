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
    
    _usuarios  = std::map<int, std::string>();
    _images = std::multimap<int,cv::Mat>();
}

AIDataSet::~AIDataSet(){

}

void AIDataSet::loadData(){
    int rows = _images.size();
    int cols = _images.begin()->second.cols * _images.begin()->second.rows;
    LOG(rows)
    LOG(cols)
    data = Eigen::MatrixXd(rows,cols);
    labels = Eigen::Matrix<int, Eigen::Dynamic, 1>(rows);
    
    //funcion inline que contruye una matriz Eigen a partir de un multimap
    STL2EIGEN(_images, data,labels);
    LOG(data.size())
    LOG(labels.size())
}

std::string AIDataSet::getNameById(int idx){
    return _usuarios.find(idx)->second;
}

void AIDataSet::loadDataFromFile(std::string filename){
    std::ifstream data_images(filename);
    if (!data_images.is_open()) {
        LOG("file not found or cant open to read data")
        
        return;
    }
    
    std::string value;
    //std::istringstream line_stream;
    std::string pix;
    
    if (data_images.good())
    {
        while (std::getline(data_images,value,'\n'))
        {
            std::istringstream line_stream(value);

            bool first = true;
            int pixel = 0;
            int clase;
            cv::Mat img = cv::Mat(cv::Size(80,80),CV_8UC1);
            int i = 0, j = 0;
            
            //se agrega una entrada en la variable _images
            while (std::getline(line_stream, pix, ','))
            {
                //LOG(pix)
                pixel = std::atoi(pix.c_str());
                if (first)
                {
                    clase = pixel;
                    first = false;
                    //LOG("clase: "<<clase)
                }
                else
                {
                    //LOG("i: "<<i<<"j: "<<j)
                    img.at<uchar>(i,j)=pixel;
                    
                    if(j < 79)
                    {
                        j++;
                    }
                    else
                    {
                        i++;
                        j = 0;
                    }
                }
                //cv::imshow("imagen", img);
            }
            
            _images.insert(std::make_pair(clase, img));
        }
    }
    
    data_images.close();
}

void AIDataSet::saveImage(int index, cv::Mat img){
    int indexTemp = _usuarios.size();
    LOG(indexTemp)
    _images.insert(std::make_pair(index, img));
}

void AIDataSet::saveUser(int index, std::string nombre){
    _usuarios.insert(std::make_pair(index, nombre));
}

void AIDataSet::saveDataToFile(std::string filename){
    std::ofstream fout(filename);
     if(!fout)
     {
         LOG("File Not Opened")
         return;
     }
     if (_images.empty())
     {
         LOG("not found images to save, < _images std::map > is empty")
         return;
     }
     std::multimap<int,cv::Mat>::iterator iter = _images.begin();
     //Writing
     //Write ros and column in one line
     //fout << _images.size() << "," << (_images.size() != 0 ? iter->second.rows * iter->second.cols : 0) << std::endl;
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
}

void AIDataSet::saveNamesToFile(std::string filename){
    std::ofstream fout(filename);
    if(!fout)
    {
        LOG("File Not Opened")
        return;
    }
    if (_images.empty())
    {
        LOG("not found names to save, < _usuarios std::map > is empty")
        return;
    }
    
    std::map<int,std::string>::iterator iter = _usuarios.begin();
    while (iter != _usuarios.end()) {
        fout<<iter->first;
        fout<<",";
        fout<<iter->second;
        fout<<"\n";
        iter++;
    }
    
    fout.close();
}

void AIDataSet::loadNamesFromFile(std::string filename){
    std::ifstream data_images(filename);
    if (!data_images.is_open()) {
        LOG("file not found or cant open to read data")
        
        return;
    }
    if (!_usuarios.empty()) {
        _usuarios.clear();
    }
    
    std::string line;
    //std::istringstream line_stream;
    std::string pix;
    int indice;
    std::string nombre;
    if (data_images.good())
    {
        while (std::getline(data_images,line,'\n'))
        {
            std::istringstream line_stream(line);
            bool first = true;
            //se agrega una entrada en la variable _usuario
            while (std::getline(line_stream, pix, ','))
            {
                if (first) {
                    indice = std::atoi( pix.c_str());
                    first = false;
                }
                else
                {
                    nombre = pix;
                }
            }
            LOG("indice: "<<indice<<" nombre: "<<nombre)
            saveUser(indice, nombre);
        }
    }
}


int AIDataSet::getLastIndex(){
    LOG("size of users: "<<_usuarios.size())
    return _usuarios.size();
}