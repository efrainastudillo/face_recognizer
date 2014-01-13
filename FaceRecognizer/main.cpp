//
//  main.cpp
//  FaceRecognizer
//
//  Created by Efrain Astudillo on 1/5/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#include "AIFaceDetection.h"
#include "AIDataSet.h"
#include <Eigen/Dense>
#include <boost/filesystem/operations.hpp>
#include <opencv2/core/eigen.hpp>
//#include <boost/filesystem/fstream.hpp>


namespace fs = boost::filesystem;

int main(int argc, const char * argv[])
{
    
    AIDataSet d;
    d.load_data("/Users/efrainastudillo/Documents/file.csv");
    
    if(d.read_images()!= AIStatus::AI_STATUS_OK){
        LOG("Error reading images")
    }
    
    d.save_images("/Users/efrainastudillo/Documents/Development/file.csv");
    LOG(d._names.size())
    LOG(d._names.at(2))
    cv::Mat img = cv::imread("/Users/efrainastudillo/Documents/Development/XcodeProjects/FaceRecognizer/FaceRecognizer/images/Adrien_Brody/Adrien_Brody_0004.jpg");

    cv::imshow("Imagen", img);
    cv::waitKey();
    
    /*
    cv::VideoCapture *capture = new cv::VideoCapture(0);
    
    if (!capture->isOpened()) {
        return 0;
    }
    
    while (true) {
        char key = cv::waitKey(2);
        if (key == 27) {
            break;
        }
        cv::Mat img;
        capture->read(img);
        
        cv::namedWindow("Imagen");
        cv::imshow("Imagen", img);
        
        //std::cout<<"loop";
    }
    
    cv::destroyAllWindows();
     */
    // insert code here...
    std::cout << "cleaned all windows!\n";
    return 0;
}

