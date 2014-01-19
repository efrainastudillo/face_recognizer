//
//  AIUtil.h
//  FaceRecognizer
//
//  Created by Efrain Astudillo on 1/7/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#ifndef FaceRecognizer_AIUtil_h
#define FaceRecognizer_AIUtil_h

#include <iostream>

enum AIStatus{AI_STATUS_OK,
    AI_STATUS_ERROR,
    AI_STATUS_UNKNOWN,
    AI_STATUS_NOT_IMAGES,
    AI_STATUS_CANT_OPEN_FILE
};

#define LOG(msg) (std::cout<<"[ AI ] => "<<msg<<std::endl);

#ifdef __APPLE__
#define __IMAGES_PATH__ "/Users/efrainastudillo/Documents/Development/XcodeProjects/FaceRecognizer/FaceRecognizer/images/"
#define __HAARCASCADE_PATH__ "/Users/efrainastudillo/Documents/Development/opencv/data/haarcascades/haarcascade_frontalface_alt.xml"
#define __TRAINING_PATH__ "/Users/efrainastudillo/Documents/Development/XcodeProjects/FaceRecognizer/FaceRecognizer/testingFiles/images_training.csv"
#define __TEST_PATH__ "/Users/efrainastudillo/Documents/Development/XcodeProjects/FaceRecognizer/FaceRecognizer/testingFiles/images_test.csv"
#define __MODEL_PATH__ "/Users/efrainastudillo/Documents/Development/XcodeProjects/FaceRecognizer/FaceRecognizer/trainingModel/"

#elif __PETER__ //Pedro Lucas Path
#define __IMAGES_PATH__ "D:/AIProject/face_recognizer/FaceRecognizer/images/"
#define __HAARCASCADE_PATH__ "D:/AIProject/face_recognizer/FaceRecognizer/data/haarcascade_frontalface_alt.xml"
#define __TRAINING_PATH__ "D:/AIProject/face_recognizer/FaceRecognizer/testingFiles/images_training.csv"
#define __TEST_PATH__ "D:/AIProject/face_recognizer/FaceRecognizer/testingFiles/images_test.csv"
#define __MODEL_PATH__ "D:/AIProject/face_recognizer/FaceRecognizer/trainingModel/"

#elif __GERMAN__ // German Villalba Path
#define __IMAGES_PATH__ "/path/german/villalba"
#define __HAARCASCADE_PATH__ ""
#define __TRAINING_PATH__ ""
#define __TEST_PATH__ ""
#define __MODEL_PATH__ ""

#else //path default
#define __IMAGES_PATH__ "/home/user/documents/"
#define __HAARCASCADE_PATH__ ""
#define __TRAINING_PATH__ ""
#define __TEST_PATH__ ""
#define __MODEL_PATH__ ""

#endif

#endif
