//
//  BaseApp.cpp
//  BaseApp
//
//  Created by Efrain Astudillo on 1/22/14.
//  Copyright (c) 2014 Efrain Astudillo. All rights reserved.
//

#include <iostream>

#include "Resources.h"

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/PolyLine.h"

#include "AICamera.h"
#include "AIFont.h"
#include "AITextInput.h"
#include "AIButton.h"


using namespace ci;
using namespace ci::app;

class TutorialApp : public AppNative {
public:
	void prepareSettings( Settings *settings ) override;
	void setup() override;
	void update() override;
	void draw() override;
    
    //events
    void keyDown(KeyEvent event) override;
    void mouseDown( MouseEvent event ) override;
    void mouseMove(MouseEvent event) override;
    
    void displayChange();
	
	gl::Texture mImage;
    std::string mMessage;
    
    
    
    AIButton mTrainButton,mBuildButton,mPredictButton;
    AIButton mSaveDataButton,mSaveModelButton;
	AICamera mCamera;
    AITextInput mTextInput;
    AIFont mFont;
	//ParticleController mParticleController;
};

void TutorialApp::prepareSettings( Settings *settings )
{
    settings->enableHighDensityDisplay();
	settings->enableMultiTouch( false );
    //settings->setFullScreen();
    settings->setWindowSize(800, 600);
    console() <<"Width: "<< settings->cinder::app::App::Settings::getDisplay()->getWidth()<<std::endl;
    
    console() << "Height: "<<settings->cinder::app::App::Settings::getDisplay()->getHeight()<<std::endl;
    console() << "Window Size: "<<settings->getWindowSize()<<std::endl;
}

void TutorialApp::setup()
{
	mImage = gl::Texture( loadImage( loadResource( BACKGROUND_IMAGE ) ) );
    mFont.initialize();    //initialize camera
    
    int top = getWindowHeight() * 0.15f;
    int bottom = getWindowHeight() * 0.8f;
    int left = getWindowWidth()/2 + 60;
    int right = getWindowWidth() * 0.9f;
    
    int height_rect = (bottom - top) / 3;
    int width_rect = (right - left);
    mTrainButton.setText("Capture",mFont);
    mBuildButton.setText("Build",mFont);
    mPredictButton.setText("Predict",mFont);
    
    mSaveDataButton.setText("Save Data", mFont);
    mSaveModelButton.setText("Save Model", mFont);
    
    mTrainButton.setPosition(ci::Rectf(left,top + height_rect*0.53,width_rect*0.45,40));
    mBuildButton.setPosition(ci::Rectf(left,top + height_rect*1.53,width_rect*0.45,40));
    mPredictButton.setPosition(ci::Rectf(left,top + height_rect*2.53,width_rect*0.45,40));
    
    mSaveDataButton.setPosition(ci::Rectf(left + width_rect*0.5,top + height_rect*0.53,width_rect*0.45,40));
    mSaveModelButton.setPosition(ci::Rectf(left + width_rect*0.5,top + height_rect*1.53,width_rect*0.45,40));
    
    mTextInput.initialize();
    //mCamera.mDataSet.loadDataFromFile(__TRAINING_PATH__);
    //mCamera.mDataSet.loadNamesFromFile(__TRAINING_NAMES_PATH__);
    mCamera.initialize();// camera initilization should be before to load names and data from files
    

    
    
    mMessage = "! Bienvenido !";
    getWindow()->getSignalDisplayChange().connect( std::bind( &TutorialApp::displayChange, this ) );
	
}

void TutorialApp::displayChange()
{
	console() << "Window display changed: " << getWindow()->getDisplay()->getBounds() << std::endl;
	console() << "ContentScale = " << getWindowContentScale() << std::endl;
	console() << "getfWindowCenter() = " << getWindowCenter() << std::endl;
}

void TutorialApp::keyDown(ci::app::KeyEvent event){
    if( event.getCode() == KeyEvent::KEY_ESCAPE )
    {
        exit(EXIT_SUCCESS);
    }
    if(event.getCode() == KeyEvent::KEY_z)
    {
        
    }
    if(event.getCode() == KeyEvent::KEY_s)
    {
        
    }
    if(event.getCode() == KeyEvent::KEY_f){
        setFullScreen(!isFullScreen());
    }
}

void TutorialApp::mouseDown(cinder::app::MouseEvent event){
    mBuildButton.MouseDown(event);
    mTrainButton.MouseDown(event);
    mPredictButton.MouseDown(event);
    mSaveDataButton.MouseDown(event);
    mSaveModelButton.MouseDown(event);
    
    if (mTrainButton.isEvent())
    {
        mCamera.enableTraining(true);
    }
    else if(mBuildButton.isEvent())
    {
        //mCamera.mDataSet.loadData();
        console()<< "Data Size: "<<mCamera.mDataSet.data.size()<<std::endl;
        console()<< "Labels Size: "<<mCamera.mDataSet.labels.size()<<std::endl;
        
        //mBuilder.compute(mCamera.mDataSet.data, mCamera.mDataSet.labels);
    }
    else if (mPredictButton.isEvent())
    {
    
    }
    else if (mSaveDataButton.isEvent())
    {
        mCamera.mDataSet.saveDataToFile(__TRAINING_PATH__);
        mCamera.mDataSet.saveNamesToFile(__TRAINING_NAMES_PATH__);
    }
    else if (mSaveModelButton.isEvent())
    {
        
    }
}
void TutorialApp::mouseMove(cinder::app::MouseEvent event){
    mBuildButton.MouseMove(event);
    mPredictButton.MouseMove(event);
    mTrainButton.MouseMove(event);
    mSaveModelButton.MouseMove(event);
    mSaveDataButton.MouseMove(event);
}
void TutorialApp::update()
{
    mCamera.update();
}

void TutorialApp::draw()
{
	gl::clear( Color( 0.1f, 0.1f, 0.15f ) );
    gl::enableAlphaBlending();
    
    int top = getWindowHeight() * 0.15f;
    int bottom = getWindowHeight() * 0.8f;
    int left = getWindowWidth() * 0.1f;
    int right = getWindowWidth() * 0.9f;
    
    int height_rect = (bottom - top) / 3;
    int gap = 10;
    
    // draw the background image
	gl::color( ColorA(1.0,1.0,1.0,0.3));
    ci::gl::draw(mImage,getWindowBounds());
    
    gl::color( ColorA(1.0,1.0,1.0,0.8));
	mCamera.draw(ci::Rectf(left,top,getWindowWidth()/2,bottom));
    
    mTrainButton.draw(Color(0.4,0.4,1.0));
    mBuildButton.draw(Color(0.4,0.4,1.0));
    mPredictButton.draw(Color(0.4,0.4,1.0));
    
    mSaveDataButton.draw(Color(0.4,0.4,1.0));
    mSaveModelButton.draw(Color(0.4,0.4,1.0));
    
    
    gl::color(Color::white());
    // The title
    std::string msg = "Face Recognizer";
	float stringWidth = mFont.getStringWidth(msg);
    mFont.draw(msg, Vec2f( getWindowWidth()/2 - stringWidth/2, 60 ),1.f);
    
    ci::gl::drawStrokedRect(ci::Rectf(getWindowWidth()/2 + 50, top, right,top + height_rect - gap));
    ci::gl::drawStrokedRect(ci::Rectf(getWindowWidth()/2 + 50, top + height_rect, right,top + height_rect*2 - gap));
    ci::gl::drawStrokedRect(ci::Rectf(getWindowWidth()/2 + 50, top + height_rect*2, right,top + height_rect*3 - gap));

    mFont.draw("Training Data", ci::Vec2d(getWindowWidth()/2 + 50 + gap,top + gap*2.6),0.5f);
    mFont.draw("Building Model", ci::Vec2d(getWindowWidth()/2 + 50 + gap,top + height_rect + gap*2.6),0.5f);
    mFont.draw("Predicting", ci::Vec2d(getWindowWidth()/2 + 50 + gap,top + height_rect*2 + gap*2.6),0.5f);
    
    mFont.draw("Mensaje General", ci::Vec2d(left + gap ,bottom + gap*5), 0.8f);
    
    gl::disableAlphaBlending();
}


CINDER_APP_NATIVE( TutorialApp, RendererGl(0) )