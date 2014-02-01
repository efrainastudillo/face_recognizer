//
//  AIFont.h
//  BaseApp
//
//  Created by Efrain Astudillo on 1/25/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#ifndef __BaseApp__AIFont__
#define __BaseApp__AIFont__

#include <iostream>
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/TextureFont.h"

class AIFont{
public:
    AIFont();
    ~AIFont(){};
    void draw(std::string msg,ci::Vec2d position,float);
    void initialize();
    float getStringWidth(std::string&);
    
    ci::gl::TextureFontRef mFont_ref;
};











#endif /* defined(__BaseApp__AIFont__) */
