//
//  main.cpp
//  FaceRecognizer
//
//  Created by Efrain Astudillo on 1/5/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#include "AIDataSet.h"
#include "AITraining.h"
#include <Eigen/Dense>
#include <boost/filesystem/operations.hpp>
#include <opencv2/core/eigen.hpp>


namespace fs = boost::filesystem;

int main(int argc, const char * argv[])
{
    /*
     
	consciente
     
    AIDataSet d;
    //d.load_data("/Users/efrainastudillo/Documents/file.csv");
    
	
    //se graba el data training
    if(d.read_images(__IMAGES_PATH__)!= AIStatus::AI_STATUS_OK){
        LOG("Error reading images")
    }
    d.save_images(__TRAINING_PATH__);
    
    d._images.clear();
    
    //se graba el data test
    if(d.read_images(__IMAGES_PATH_TEST__)!= AIStatus::AI_STATUS_OK){
        LOG("Error reading images")
    }
    d.save_images(__TEST_PATH__);
    
    d._images.clear();
    cv::waitKey();*/
    
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


	std::string pathTraining = __TRAINING_PATH__;
	/*AIDataSet d;

	if (d.read_images(__IMAGES_PATH__) != AIStatus::AI_STATUS_OK){
		LOG("Error reading images")
	}

	d.save_images(pathTraining);
     */
	
	//AITraining training;

	//training.Test(pathTraining);
    
    //std::cout<< M.inverse() <<std::endl;

    std::cout << "cleaned all windows!\n";
	//std::cin.get();
    return 0;
}

