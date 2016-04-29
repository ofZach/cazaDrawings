#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    for(int i = 0; i < NUM_CONES; i++){
        conics[i].setRadius(40 + 4*i);
        conics[i].setPosition( ofVec3f(0, 0, 0) );
        conics[i].setLookAt( ofVec3f(0, 0, 1) );
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofClear(0);
    ofSetLineWidth(1);
    
    cam.begin();
    ofScale(2, 2, 2);
//    ofDrawAxis(20);
    
    ofSetColor(255, 10);
    for(int i = 0 ;i < NUM_CONES; i++)
        conics[i].draw();
    
    ofSetColor(255, 128);
    
    static float PHI_ANGLE = 0.618 * M_PI;

    for(int i = 0 ;i < NUM_CONES; i++){
        float diff = powf(sinf(ofGetElapsedTimef()*.2222), 2);
        float diff2 = powf(sinf(ofGetElapsedTimef()*.487), 2);
        conics[i].setLookAt( ofVec3f(0,
                                     0,
                                     1) );
        plane = ofVec3f(0,
                        0,
                        100 + 80*cosf(ofGetElapsedTimef()));
        planeNormal = ofVec3f(80 + 80*cosf(ofGetElapsedTimef()*.444),
                              80 + 80*sinf(ofGetElapsedTimef()*.5),
                              20);
        conics[i].fillIntersectionsWithPlane(plane, planeNormal);
    }

    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
