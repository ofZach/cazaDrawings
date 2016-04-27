#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Polychron.h"

#define NUM_POLY 20

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

    
    ofEasyCam cam;
    
    Polychron polychron[NUM_POLY];
    ofVec3f rotations[NUM_POLY];
    
    ofxPanel gui;
    // hypercubes
    ofxIntSlider numPoly;
    ofxFloatSlider radiusScale;
    ofxVec3Slider angleOffset;
    ofxToggle fourDAnimated;
    ofxVec3Slider fourD;
    ofxVec3Slider compression;

    ofxToggle rotAnimations;
    ofxFloatSlider rotAnimSpeed;
    ofxFloatSlider rotAnimMag;

    ofxToggle posAnimations;
    ofxFloatSlider posAnimSpeed;
    ofxFloatSlider posAnimMag;

    // camera
    ofxFloatSlider cameraDistance;
    ofxToggle autoCamera;

//    ofxColorSlider color;
//    ofxButton ringButton;
//    ofxLabel screenSize;
};
