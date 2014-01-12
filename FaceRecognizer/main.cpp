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
    d.read_images();
    //"/Users/efrainastudillo/Documents/Development/file.csv"   ==> efrain
    // put your path                                            ==> pedro
    // put yout path                                            ==> daniel
    // since we will be constantly changing the path, we could forget our path
    // and avoid lose time finding again over again.
    //d.save_images("/Users/efrainastudillo/Documents/Development/file.csv");
	d.save_images("D:/AIProject/Tests/file.csv");
    
    //cv::Mat img = cv::imread("/Users/efrainastudillo/scikit_learn_data/Adrien_Brody/Adrien_Brody_0004.jpg");
	cv::Mat img = cv::imread("D:/miles.jpg");
    cv::imshow("Imagen", img);
    if (d._images.size()>0) {
        cv::imshow("Other image", d._images[2]);
    }
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

