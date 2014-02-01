//
//  AIButton.h
//  BaseApp
//
//  Created by Efrain Astudillo on 1/26/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#ifndef __BaseApp__AIButton__
#define __BaseApp__AIButton__

#include <iostream>
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/TextureFont.h"

#include "AIFont.h"

class AIButton{
public:
    
    AIButton();
    ~AIButton(){};
    
    void draw(ci::Color color);
    void MouseDown(ci::app::MouseEvent mouse);
    void MouseMove(ci::app::MouseEvent mouse);
    void setText(std::string,AIFont&);
    void setPosition(ci::Rectf);
    bool isEvent();
    
    
    AIFont mFont;
    bool mEntered;
    bool mEventGenerated;
    bool mPress;
    
    ci::Vec2d mPosition;
    std::string mText;
    ci::Rectf mRect;
};

#endif /* defined(__BaseApp__AIButton__) */
