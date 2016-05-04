#pragma once

#include "ofMain.h"
#include "Conics.h"
#include "ofxGui.h"

#define NUM_CONES 64
#define NUM_PLANES 3

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
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
