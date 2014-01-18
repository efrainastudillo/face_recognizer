//
//  AITechnique.h
//  FaceRecognizer
//
//  Created by Efrain Astudillo on 1/18/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#ifndef FaceRecognizer_AITechnique_h
#define FaceRecognizer_AITechnique_h
class _AITecnique{
public:
    virtual void _compute() = 0;
    virtual void _extract() = 0;
};
class AIPca : public _AITecnique{
public:
    AIPca();
    
    void _compute();
    void _extract();
    
};

class AILda : public _AITecnique{
public:
    AILda();
    
    void _compute();
    void _extract();
    
};

#endif
