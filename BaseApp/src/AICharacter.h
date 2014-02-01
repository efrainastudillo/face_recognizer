//
//  AICharacter.h
//  BaseApp
//
//  Created by Efrain Astudillo on 1/25/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#ifndef __BaseApp__AICharacter__
#define __BaseApp__AICharacter__

#include "cinder/gl/TextureFont.h"
#include "cinder/Timeline.h"
#include "cinder/Vector.h"
#include "cinder/Color.h"
#include "cinder/Rect.h"


class Character {
public:
	Character() {}
	Character( ci::gl::TextureFontRef textureFont, std::string character,  ci::Matrix44f matrix );
	
	void	animIn( ci::Timeline &timeline,  ci::Matrix44f matrix );
	void	animOut( ci::Timeline &timeline,  ci::Matrix44f matrix );
	
	void	draw() const;
	
	ci::Rectf		getKernBounds() const;
	bool            isDead() const;
	ci::Matrix44f	getDestMatrix() const;
	
protected:
	void	onAnimOut();
	
	ci::Anim<ci::ColorAf>			mColorCur;
	ci::Anim<ci::Matrix44f>			mMatrix;
	
	ci::ColorAf					mColorStart, mColorDest;
	
	ci::Matrix44f				mDestMatrix;
	
	std::string					mChar;
	
	ci::gl::TextureFontRef		mTextureFont;
	ci::Rectf					mKernBounds;
	
	bool					mIsDead;
};

#endif /* defined(__BaseApp__AICharacter__) */
