#pragma once

#include "ofMain.h"
#include "BaseScene.h"
#include "Conics.h"
#include "ofxGui.h"

#define NUM_CONES 64
#define NUM_PLANES 3

class ConicsScene : public BaseScene{

	public:
		void setup();
		void update();
		void draw();
		
    Conics conics[NUM_CONES];
    
    ofVec3f plane, planeNormal;
    
    ofVec3f movingPlane, movingPlaneNormal;

    ofEasyCam cam;

    ofxPanel gui;
    // hypercubes
    ofxIntSlider numCones;
    ofxIntSlider numPlanes;
    
    ofxFloatSlider planeXY;
    ofxFloatSlider planeXYPeriod;
    ofxFloatSlider planeXYPhase;
    ofxFloatSlider planeZ;
    ofxFloatSlider planeZPeriod;
    ofxFloatSlider planeZPhase;

    ofxFloatSlider planeXYTilt;
    ofxFloatSlider planeXYTiltPeriod;
    ofxFloatSlider planeXYTiltPhase;
    ofxFloatSlider planeZTilt;
    ofxFloatSlider planeZTiltPeriod;
    ofxFloatSlider planeZTiltPhase;

    ofxToggle coneAnimate;
    ofxFloatSlider coneLookPeriod;
    ofxFloatSlider coneLookPhase;
    ofxFloatSlider conePeriod;
    ofxFloatSlider conePhase;
    ofxFloatSlider coneMagnitude;
    ofxFloatSlider coneZPeriod;
    ofxFloatSlider coneZPhase;
    ofxFloatSlider coneZMagnitude;

    
    ofxVec3Slider angleOffset;
    ofxToggle indexed;
    ofxToggle fourDAnimated;
    ofxVec3Slider fourD;
    ofxVec3Slider compression;
    ofxFloatSlider gridGap;

};
