//
//  AIButton.cpp
//  BaseApp
//
//  Created by Efrain Astudillo on 1/26/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#include "AIButton.h"


AIButton::AIButton(){
    mPress = false;
    mEntered = false;
    mEventGenerated = false;
    mText = "AIButton";
    mRect = ci::Rectf(0,0,0,0);
    mPosition = ci::Vec2d(0,0);
}

void AIButton::draw(ci::Color color){

    if (!mEntered) {
        ci::gl::color(color);
    }
    else if(mPress)
    {
        ci::gl::color(ci::Color(0.2,0.2,1.0));
        mPress = false;
    }
    else
    {
        ci::gl::color(ci::Color(0.7,0.7,1.0));
    }
    ci::gl::drawSolidRect(ci::Rectf(mRect.x1,mRect.y1,mRect.x1 + mRect.x2, mRect.y1 + mRect.y2));
    int lengthText = mFont.getStringWidth(mText);
    
    ci::gl::color(ci::Color::white());
    mFont.draw(mText, ci::Vec2d(mRect.x1 + 30 + (mRect.x2/2 - lengthText/2),mRect.y1 + mRect.y2 - 15),0.7f);
}

void AIButton::MouseDown(ci::app::MouseEvent mouse){
    ci::Vec2i pos;
    if (mouse.isLeftDown()) {
        pos = mouse.getPos();
        if(pos.x > mRect.x1 && pos.x < mRect.x1 + mRect.x2 && pos.y > mRect.y1 && pos.y < mRect.y2 + mRect.y1){
            mEventGenerated = true;
            mPress = true;
        }
        else
        {
            mEventGenerated = false;
        }
    }

}
void AIButton::MouseMove(ci::app::MouseEvent mouse){
    ci::Vec2i pos = mouse.getPos();
    if(pos.x > mRect.x1 && pos.x < mRect.x1 + mRect.x2 && pos.y > mRect.y1 && pos.y < mRect.y2 + mRect.y1){
        mEntered = true;
    }
    else
    {
        mEntered = false;
    }
}
// x, y , width, and height
void AIButton::setPosition(ci::Rectf rect){
    mRect = rect;
}

void AIButton::setText(std::string text,AIFont &m){
    mFont = m;
    mText = text;
}

bool AIButton::isEvent(){
    return mEventGenerated;
}

