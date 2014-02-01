//
//  AITextInput.cpp
//  BaseApp
//
//  Created by Efrain Astudillo on 1/25/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#include "AITextInput.h"



void AITextInput::initialize(){
    // font
    ci::Font customFont( ci::Font( ci::app::loadResource( RES_CUSTOM_FONT ), 100 ) );
    ci::gl::TextureFont::Format f;
	f.enableMipmapping( true );
	mTextureFont = ci::gl::TextureFont::create( customFont, f );
    
    // scene
	mSceneMatrix = mSceneDestMatrix = Matrix44f::identity();
    
    // camera
	mCamDist = 600.0f;
	mCam.setPerspective( 75.0f, getWindowAspectRatio(), 0.1f, 5000.0f );
	mCam.lookAt( Vec3f( 0.0f, 0.0f, mCamDist ), Vec3f::zero(), Vec3f::yAxis() );
}

void AITextInput::keyDown( KeyEvent event ){
    
    char ch = event.getChar();
	string specialChars = " .,:;/?\\!@#%^&*()-_=+[]<>'\""; // the remaining characters that the font provides
	
	if( event.getCode() == KeyEvent::KEY_BACKSPACE )
		removeChar();
	else if( isalnum( ch ) )
		addChar( ch );
	else if( specialChars.find( ch ) != -1 )
		addChar( ch );
}

void AITextInput::update(){

}
void AITextInput::draw(){

}

void AITextInput::addChar( char c ){

}
void AITextInput::removeChar(){

}