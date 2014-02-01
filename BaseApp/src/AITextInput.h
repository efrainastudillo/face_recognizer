//
//  AITextInput.h
//  BaseApp
//
//  Created by Efrain Astudillo on 1/25/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#ifndef __BaseApp__AITextInput__
#define __BaseApp__AITextInput__

#include <iostream>

#include "cinder/gl/gl.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/Camera.h"
#include "cinder/Rand.h"
#include <vector>
#include <list>

#include "AICharacter.h"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class AITextInput{
public:
    
    void keyDown( KeyEvent event );
	void update();
	void draw();
	
	void addChar( char c );
	void removeChar();
    
    void initialize();
    
    vector<Character>	mCharacters;
	list<Character>		mDyingCharacters;
    string				mText;
	
	CameraPersp			mCam;
	float				mCamDist;
    
    ci::gl::TextureFontRef  mTextureFont;
    Anim<Matrix44f>         mSceneMatrix;
	Matrix44f               mSceneDestMatrix;
};

#endif /* defined(__BaseApp__AITextInput__) */
