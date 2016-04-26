#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    ofNoFill();
    for(int i = 0; i < NUM_CONES; i++){
        conics[i].setRadius(50 + 10*i);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    float SPEED = .2;
    float diff = .3 * sinf(ofGetElapsedTimef()*.2);
    for(int i = 0 ;i < NUM_CONES; i++){
        conics[i].setPosition( ofVec3f(400*ofNoise(ofGetElapsedTimef()*SPEED + diff*i)-200,
                                       400*ofNoise(10+ofGetElapsedTimef()*SPEED + diff*i)-200,
                                       0) );
//        conics[i].setHeight(300 + 250 * sinf(2*i+ofGetElapsedTimef()));
//        conics[i].setRadius(100 + 90 * sinf(2*i+ofGetElapsedTimef()*.3));
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofClear(0);
    ofSetLineWidth(1);
    
    cam.begin();
    ofDrawAxis(20);
    
    ofSetColor(255, 10);
    for(int i = 0 ;i < NUM_CONES; i++)
        conics[i].draw();
    
    ofSetColor(0, 128, 255);
    plane = ofVec3f(0, 25, 0);
    planeNormal = ofVec3f(0, 1, 0);
    for(int i = 0 ;i < NUM_CONES; i++)
        conics[i].drawIntersectionsWithPlane(plane, planeNormal);

    ofSetColor(0, 255, 128);
    plane = ofVec3f(0, 0, -50);
    planeNormal = ofVec3f(0, 0, 1);
    for(int i = 0 ;i < NUM_CONES; i++)
        conics[i].drawIntersectionsWithPlane(plane, planeNormal);

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
