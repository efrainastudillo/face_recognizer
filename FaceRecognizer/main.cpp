//
//  main.cpp
//  FaceRecognizer
//
//  Created by Efrain Astudillo on 1/5/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <Eigen/Dense>



int main(int argc, const char * argv[])
{
    Eigen::MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    std::cout << "Here is the matrix m:\n" << m << std::endl;
    
    
    
    cv::VideoCapture *capture = new cv::VideoCapture(0);
    
    if (capture->isOpened()) {
        std::cout<<"Opened"<<std::endl;
    }
    else
        return 0;
    
    while (true) {
        char key = cv::waitKey(2);
        if (key == 27) {
            return 0;
        }
        cv::Mat img;
        capture->read(img);
        
        cv::namedWindow("Imagen");
        cv::imshow("Imagen", img);
        
        //std::cout<<"loop";
    }
    cv::Mat image;
    
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

