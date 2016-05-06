//
//  SceneManager.hpp
//  sceneSwitcher
//
//  Created by Robby on 5/6/16.
//
//

#ifndef SceneManager_hpp
#define SceneManager_hpp

#include "ofMain.h"
#include "BaseScene.h"
#include "ofxGui.h"
#include <stdio.h>


#define FADE_DELAY_MIN 1.4
#define FADE_DELAY_MAX 1.67

#define SCENE_PRE_TRANSITION_FADE   0.4
#define SCENE_PRE_TRANSITION_CURSOR 0.5

class SceneManager {
    
private:
    void nextScene(bool forward);
    
public:
    
    ~SceneManager();
    vector<BaseScene*> scenes;
    int currentScene;
    
    void setup();
    void update();
    void draw();
    
    void advanceScene();
//    void regressScene();
    
    ofPoint centroid, lastCentroid;
    ofPixels lastFrame, currFrame;
    
    void startScene(int whichScene);
    
    ofFbo transitionFbo;
    ofFbo sceneFbo;
    ofFbo dimmedSceneFbo;

    ofShader dimmerShader;
    
    ofxPanel gui;
    ofParameter<bool>bAutoPlay, bSceneWaitForCode, bFadeOut, bAutoAdvance, drawScenePanel, enableMidiUpdate, enableParameterSounds;
    ofParameter<float> autoadvanceDelay, ofSmoothing;
    float lastAutoadvanceTime;
};


#endif /* SceneManager_hpp */
