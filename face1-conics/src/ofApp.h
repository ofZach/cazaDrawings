#pragma once

#include "ofMain.h"
#include "pointLoader.hpp"
#include "Conics.h"

#define NUM_CONES 3

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
		
        pointLoader PL;
    
    ofEasyCam cam;
    Conics mouthCones[NUM_CONES];
    
    ofVec3f plane, planeNormal;
    
};
