#pragma once

#include "ofMain.h"

class Point4D : public ofBaseApp{
public:
    float x, y, z, w;
    Point4D();
    Point4D(float x, float y, float z, float w);

    void rotate(ofMatrix4x4 m);
};

class Polychron : public ofBaseApp {
public:
    void loadVefFile(string file);
    void drawWireframe();
    void rotate(ofMatrix4x4 m); // note: all 4 cols/rows are used for rotation, not 3 with 1 translation like traditional 3D graphics
    void log();  // printf vertices, edges, faces

private:// or maybe public
    vector<Point4D> vertices;
    vector<unsigned int> edges; // indices in vertices array
    vector<unsigned int> faces;  // indices in vertices array
    unsigned int verticesPerFace; // TODO

// definitely private
    vector<Point4D> _v;
    vector<unsigned int> _e;
    vector<unsigned int> _f;
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

    Polychron polychron;
    
    ofEasyCam cam;
    
    float a1, a2, a3; // angle of rotations
};
