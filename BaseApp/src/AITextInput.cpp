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
}

void AITextInput::keyDown( KeyEvent event ){
    
    char ch = event.getChar();
	string specialChars = " .,:;/?\\!@#%^&*()-_=+[]<>'\""; // the remaining characters that the font provides
	
	if( event.getCode() == KeyEvent::KEY_BACKSPACE )
    {
		removeChar();
        console()<< "remove characterl"<<std::endl;
    }
	else if( isalnum( ch ) )
    {
		addChar( ch );
        console()<< "addded characeter"<<std::endl;
    }
	else if( specialChars.find( ch ) != -1 )
    {
		addChar( ch );
        console()<< "especial character"<<std::endl;
    }
}
std::string AITextInput::getText(){
    std::string name = "";
    for( vector<Character>::iterator it = mCharacters.begin(); it != mCharacters.end(); ++it )
		name.append(it->mChar);
    return name;
}
void AITextInput::update(){

}
void AITextInput::draw(){
    
    ci::gl::color(1.0, 1.0, 1.0);
    /*mTextureFont->drawString( "Hello World", ci::Vec2d(100,200),
                          ci::gl::TextureFont::DrawOptions().scale( 1.0 ).pixelSnap( true ) );*/
	for( vector<Character>::iterator it = mCharacters.begin(); it != mCharacters.end(); ++it )
		it->draw();
    
}

void AITextInput::addChar( char c ){
    c = tolower( c ); // Alphabet-IV.tff seems to be missing some capital letters (strange, since it's an all-caps font)
	mCharacters.push_back( Character( mTextureFont, string( &c, 1 ) ,mCharacters.size()) );
    //console()<< "size: "<<mCharacters.size()<<std::endl;

}
void AITextInput::removeChar(){
    if( ! mCharacters.empty() ) {
		mCharacters.pop_back();
	}
}