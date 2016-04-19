#pragma once

#include "ofMain.h"
#include "Polychron.h"

#define NUM_POLY 2

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

    Polychron polychron[NUM_POLY];
    vector<float> energy[NUM_POLY];  // size of vertices
    vector<unsigned int> highlighted[NUM_POLY];

    ofEasyCam cam;
    
    ofVec3f worldToScreen(ofVec3f WorldXYZ, ofMatrix4x4 additionalTransform);

    ofPoint hotSpot;
    float hotSpotRadius;
    
    bool pointInHotspot(ofPoint point);
};
