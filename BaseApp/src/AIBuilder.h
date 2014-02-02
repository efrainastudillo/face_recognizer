//
//  AIBuilder.h
//  BaseApp
//
//  Created by Efrain Astudillo on 2/1/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#ifndef __BaseApp__AIBuilder__
#define __BaseApp__AIBuilder__

#include <iostream>
#include <string>
#include "AIClassifier.h"
#include "AITecnique.h"
#include "AIModel.h"
#include "Eigen/Dense"
#include "AIFile.h"

class AIBuilder{
public:

    AIBuilder():mTecnique(NULL),mClassifier(NULL){};
    AIBuilder(_AITecnique&,_AIClassifier&);
    void compute(const Eigen::MatrixXd& X, const Eigen::Matrix<int, Eigen::Dynamic, 1>& y);
    AIModel::DataLabel predict(const Eigen::RowVectorXd& X);
    
    
    _AITecnique *mTecnique;
    _AIClassifier *mClassifier;
};

#endif /* defined(__BaseApp__AIBuilder__) */
