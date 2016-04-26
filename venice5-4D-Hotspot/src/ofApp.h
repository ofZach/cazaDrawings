#pragma once

#include "ofMain.h"
#include "Polychron.h"

#define NUM_POLY 6

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
    vector<unsigned int> highlighted[NUM_POLY];
    
    ofVec3f rotations[NUM_POLY];
    
    // any transformation has to be run through here, if is to be reverse-calculated back into 2D screen coords
    ofMatrix4x4 polyMatrix[NUM_POLY];
    ofMatrix4x4 faceMatrix;

    ofVec3f worldToScreen(ofVec3f WorldXYZ, ofMatrix4x4 additionalTransform);

    vector<ofPoint> hotSpots;
    float hotSpotRadius;
    
    bool pointInHotspot(ofPoint hotspot, ofPoint point);

    ofShader myShader;
};
