#pragma once

#include "ofMain.h"
#include "ofxSvg.h"

class SVGMesh : public ofBaseApp{

public:
    vector<ofPoint> vertices;
    vector<unsigned int> lines; // (mult of 2) pairs of indexes to points = line start+end
    
    void loadSVG(string path);
    void draw();
    void update(); // moves points according to velocities, decays velocities
    
    // action
    
    void pushVertices(ofVec3f force);

private:
    vector<ofPoint> homeVertices;
    vector<float> inertia;

    void addVertex(ofPoint point); // adds to <ofPoint>vertices only if it's unique
    bool pointsAreEqual(ofPoint p1, ofPoint p2, float radius); // radius is in pixels,
    // sets the argument "index" to be the index of matching point in <ofPoint>vertices
    bool indexOfVertexMatchingPoint(unsigned int *index, ofPoint point, float radius);
};



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

    
    ofxSVG svg;
    float step;
    float stepVel;
    vector<ofPolyline> outlines;
    // turning SVG into openGL points and lines
    SVGMesh obj;

};
