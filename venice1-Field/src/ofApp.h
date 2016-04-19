#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#define COLUMNS 8
#define ROWS 8

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
    
    ofxPanel gui;
    ofxFloatSlider columnA;
    ofxFloatSlider columnB;
    ofxFloatSlider columnC;
    ofxFloatSlider rowA;
    ofxFloatSlider rowB;
    ofxFloatSlider rowC;
    ofxToggle diagonals;

    ofxFloatSlider COLUMN; // width / height of cells
    ofxFloatSlider ROW;

    ofxVec2Slider stretch;
    ofxVec2Slider skew;
    ofxFloatSlider wave;

    void guiUpdate(float &newValue);
        
    float rows[ROWS];
    float columns[COLUMNS];
    
    int centerX, centerY;
    
//    int COLUMN, ROW;
    
    void drawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

};
