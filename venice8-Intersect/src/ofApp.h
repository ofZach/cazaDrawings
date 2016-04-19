#pragma once

#include "ofMain.h"
#include "ofxRay.h"

#define CONE_RESOLUTION 1000
#define CONE_RADIUS 50
#define CONE_HEIGHT 100

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
    
    // the intersecting plane
    ofPoint planeMouseOffset;
    ofxRay::Plane plane;

    // cones
    ofConePrimitive topCone;
    ofConePrimitive bottomCone;
    vector<ofxRay::Ray> rays;
    ofxRay::Plane topPlane;
    ofxRay::Plane bottomPlane;
    
    // intersections
    vector<ofPoint> intersections;
    vector<ofPolyline>intersectionLines;
};
