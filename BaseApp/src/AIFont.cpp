//
//  AIFont.cpp
//  BaseApp
//
//  Created by Efrain Astudillo on 1/25/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#include "AIFont.h"


AIFont::AIFont(){
    // A font suitable for 24points at both Retina and non-Retina
	//mFont_ref = ci::gl::TextureFont::create( ci::Font( "Helvetica", 24 * 2 ), ci::gl::TextureFont::Format().enableMipmapping() );
}

float AIFont::getStringWidth(std::string& msg){
    return mFont_ref->measureString( msg ).x;
}

void AIFont::draw(std::string msg, ci::Vec2d position,float scale){
    // The font has been made double the size we need for non-Retina, so we always scale by 0.5f
	// another strategy would be to use two different TextureFonts
	mFont_ref->drawString( msg, position,
                          ci::gl::TextureFont::DrawOptions().scale( scale ).pixelSnap( true ) );
}

void AIFont::initialize(){
    mFont_ref = ci::gl::TextureFont::create( ci::Font( "Helvetica", 24 * 2 ), ci::gl::TextureFont::Format().enableMipmapping(true) );
}