#pragma once

#include "ofMain.h"


class circle {
    public :

    ofPoint pos;
    ofPoint vel;
    float radius;
    ofPoint frc;
    
    void draw(){
        ofFill();
        ofCircle(pos,2);
        ofNoFill();
        ofCircle(pos, radius);
    }
    
    void updateStart(){
        frc = ofPoint(0,0);
    }
    
    void repelFrom(circle & c){
        float totalradii = radius + c.radius;
       
        ofPoint diff = (pos - c.pos);
        float dist = diff.length();
        if (dist < totalradii){
            pos += diff.getNormalized() * (totalradii-dist) * 0.5;
            c.pos -= diff.getNormalized() * (totalradii-dist) * 0.5;
        }
    }
    
    void addForce(ofPoint toadd){
        frc += toadd;
    }
    
    
    void updateEnd(){
        vel += frc;
        pos += vel;
        vel *= 0.9;
    }
    
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
		
    
        vector < circle > circles;
    
    
};
