#pragma once

#include "ofMain.h"
#include "Conics.h"

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
		
    ofVec3f crossProduct(ofVec3f A1, ofVec3f A2);
    float dotProduct(ofVec3f A1, ofVec3f A2);
    bool linePlaneIntersect(ofVec3f *intersection, ofVec3f line0, ofVec3f line1, ofVec3f planeP, ofVec3f planeN);
    
    ofVec3f plane, planeNormal;
    ofVec3f p1, p2;
    
    float angle;
    ofEasyCam cam;
    ofNode node;
    ofNode node2;
    
    Conics conics;
    
};
