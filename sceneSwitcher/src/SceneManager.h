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

class SceneManager {
    
private:
    void nextScene(bool forward);
    
public:
    
    ~SceneManager();
    vector<BaseScene*> scenes;
    int currentScene, lastScene;
    
    void setup();
    void update();
    void draw();
    
    void advanceScene();
//    void regressScene();
    void startScene(int whichScene);
    
    ofFbo sceneFbo;
    ofFbo lastSceneFbo;

    ofShader dimmerShader;
    
    float SCENE_INTERVAL = 5; // seconds
    float FADE_DURATION = 1.0;  // shorter than SCENE_INTERVAL

    bool isFading;
    unsigned long fadeStartTime;
    
    ofxPanel gui;
    ofParameter<bool>bAutoPlay, bSceneWaitForCode, bFadeOut, bAutoAdvance, drawScenePanel, enableMidiUpdate, enableParameterSounds;
    ofParameter<float> autoadvanceDelay, ofSmoothing;
    float lastAutoadvanceTime;
};

#endif /* SceneManager_hpp */