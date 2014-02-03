//
//  AICharacter.cpp
//  BaseApp
//
//  Created by Efrain Astudillo on 1/25/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#include "AICharacter.h"


#include "cinder/Timeline.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/Easing.h"
#include "cinder/Rand.h"


using namespace ci;
using namespace std;

Character::Character( gl::TextureFontRef textureFont, string character ,int index)
{
	mTextureFont = textureFont;
	mChar = character;
	
	mColorStart = ColorAf( 1.0f, 0.5f, 0.0f, 0.0f );
	mColorCur	= mColorStart;
	
	float hue = Rand::randFloat( 0.55f, 0.6f );
	float sat = Rand::randFloat( 0.5f, 1.0f );
	mColorDest	= ColorAf( CM_HSV, hue, sat, 1.0f, 1.0f );
	
	mKernBounds = Rectf( 400, 80.0f, mTextureFont->measureString( mChar ).x, mTextureFont->getAscent() );
	position = ci::Vec2d(455 + (20 * index) ,150);
	//position = pos;
    mIsDead = false;
}

void Character::animIn( Timeline &timeline, Matrix44f matrix )
{
	mDestMatrix = matrix;
	timeline.apply( &mColorCur, mColorDest, 1.0f, EaseOutAtan( 20 ) );
	timeline.apply( &mMatrix, matrix, 0.5f, EaseOutAtan( 10 ) );
}

void Character::animOut( Timeline &timeline, Matrix44f matrix )
{
	mDestMatrix = matrix;
	timeline.apply( &mColorCur, mColorStart, 1.0f, EaseOutQuad() ).finishFn( bind( &Character::onAnimOut, this ) );
	timeline.apply( &mMatrix, matrix, 1.0f, EaseOutQuad() );
}

void Character::onAnimOut()
{
	mIsDead = true;
}

Rectf Character::getKernBounds() const
{
	return mKernBounds;
}

bool Character::isDead() const
{
	return mIsDead;
}

Matrix44f Character::getDestMatrix() const
{
	return mDestMatrix;
}

void Character::draw() const
{
    mTextureFont->drawString( mChar, position,
    ci::gl::TextureFont::DrawOptions().scale( 0.2 ).pixelSnap( true ) );
}
