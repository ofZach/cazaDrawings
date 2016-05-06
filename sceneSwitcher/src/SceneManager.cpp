//
//  SceneManager.cpp
//  sceneSwitcher
//
//  Created by Robby on 5/6/16.
//
//

#include "SceneManager.h"

#include "appConstants.h"
#include "ExampleScene.h"

//-----------------------------------------------------------------------------------
SceneManager::~SceneManager(){
//    ofRemoveListener(sync.ffwKeyPressed, this, &sceneManager::setAdvanceCurrentScene);
}
//-----------------------------------------------------------------------------------
void SceneManager::setup(){
    
    scenes.push_back(new ExampleScene());
//    scenes.push_back(new olegVeraV());
//    scenes.push_back(new sarahgpRileyCircle());
//    scenes.push_back(new mwalczykVeraSquares());
    
    gui.setDefaultWidth(300);
    gui.setup("Control Panel", "SFPC_d4n_general_settings.xml");
    
    gui.add(enableParameterSounds.set("Enable parameter sounds", true));
//    enableParameterSounds.addListener(this, &SceneManager::toggleParameterSounds);
    gui.add(drawScenePanel.set("draw scene ctrl", true));
    gui.add(enableMidiUpdate.set("enable midi update", true));
    gui.add(bAutoPlay.set("Auto Play on scene change", false));
    gui.add(autoadvanceDelay.set("Autoadvance", 0, 0, 60));
    gui.add(bSceneWaitForCode.set("Scene wait for code", true));
    gui.add(bFadeOut.set("Scene fade out", true));
    gui.add(bAutoAdvance.set("Auto Advance Scene", false));
    
    gui.setPosition(ofGetWidth() - gui.getShape().width-20,  ofGetHeight() - gui.getShape().getHeight() - 100);
    
    
    sceneFbo.allocate(VISUALS_WIDTH, VISUALS_HEIGHT, GL_RGBA, 4);
    dimmedSceneFbo.allocate(VISUALS_WIDTH, VISUALS_HEIGHT, GL_RGBA, 4);
    dimmerShader.load("dimmer");
    
    lastFrame.allocate(VISUALS_WIDTH, VISUALS_HEIGHT, OF_PIXELS_RGBA);
    currFrame.allocate(VISUALS_WIDTH, VISUALS_HEIGHT, OF_PIXELS_RGBA);
    
    //  transitionFbo.allocate(VISUALS_WIDTH, VISUALS_HEIGHT, GL_RGB32F_ARB);
    transitionFbo.begin();
    ofSetColor(0,255);
    ofDrawRectangle(0, 0, VISUALS_WIDTH, VISUALS_HEIGHT);
    transitionFbo.end();
    transitionFbo.draw(0,0);
    
    
    // disney
    for (auto scene : scenes){
        scene->dimensions.set(0,0,VISUALS_WIDTH, VISUALS_HEIGHT);
        scene->setup();
    }
    
    currentScene = 0;
    
    startScene(currentScene);
}
//-----------------------------------------------------------------------------------

void SceneManager::startScene(int whichScene){
//    scenes[currentScene]->resetTiming();
//    scenes[currentScene]->reset();
}

void SceneManager::advanceScene(){
    
}

void SceneManager::nextScene(bool forward){
    
}
//-----------------------------------------------------------------------------------
void SceneManager::update(){
    scenes[currentScene]->update();
}

//-----------------------------------------------------------------------------------
void SceneManager::draw(){

    ofClear(0,0,0,255);
    
    ofSetColor(255);
    
    // Get rid of blended sidebars
    ofSetColor(0);
    ofDrawRectangle(CODE_X_POS-1, 0, VISUALS_WIDTH+2, VISUALS_HEIGHT);
    ofSetColor(255);
    
    if (true){//shouldDrawScene) {
        sceneFbo.begin();
        ofClear(0,0,0,255);
        ofPushStyle();
        scenes[currentScene]->draw();
        ofPopStyle();
        sceneFbo.end();
        
        dimmedSceneFbo.begin();
        dimmerShader.begin();
        dimmerShader.setUniformTexture("texture0", sceneFbo.getTexture(), 0);
//        dimmerShader.setUniform1f("dimAmt", dimAmt);
        ofSetColor(255);
        ofClearAlpha();
        ofDrawRectangle(0, 0, VISUALS_WIDTH, VISUALS_HEIGHT);
        dimmerShader.end();
        dimmedSceneFbo.end();
        dimmedSceneFbo.draw(1,0,VISUALS_WIDTH, VISUALS_HEIGHT);
        dimmedSceneFbo.draw(0,0,VISUALS_WIDTH, VISUALS_HEIGHT);
        
    } else {
        ofSetColor(0);
        ofFill();
        ofClearAlpha();
        ofDrawRectangle(0, 0, VISUALS_WIDTH+1, VISUALS_HEIGHT);
    }
    
    sceneFbo.draw(0, 0);
    
    // Draw overlay rectangles on fade out
//    if (isTransitioning && fadingOut) {
//        float fadeOpacityRaw = ofMap(preTransitionPct, 0, SCENE_PRE_TRANSITION_FADE, 0, 1);
//        ofSetColor(0, ofClamp(fadeOpacityRaw * 255, 0, 255));
//        ofFill();
//        
//        // Draw over the frames
//        ofDrawRectangle(0, 0, VISUALS_WIDTH+1, VISUALS_HEIGHT);
//        ofDrawRectangle(CODE_X_POS-1, 0, VISUALS_WIDTH+2, VISUALS_HEIGHT);
//    }
    
    gui.draw();
    
}

