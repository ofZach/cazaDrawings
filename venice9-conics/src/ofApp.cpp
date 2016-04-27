#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    ofNoFill();
    for(int i = 0; i < NUM_CONES; i++){
        conics[i].setRadius(50 + i);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    float SPEED = .2;
    float diff = .3 * sinf(ofGetElapsedTimef()*.2);
    for(int i = 0 ;i < NUM_CONES; i++){
        conics[i].setPosition( ofPoint(i * 10,0, 200 + 190 * sin(ofGetElapsedTimef() + i/100.0)));
        //conics[i].setHeight(300 + 250 * sinf(2*i+ofGetElapsedTimef()));
        conics[i].setRadius(mouseX + (mouseX*0.9) * ofSignedNoise(ofGetElapsedTimef()*.3, i/10.0));
        
        conics[i].setLookAt( ofPoint(200 + 100 * sin(ofGetElapsedTimef() + i/100.0), 0 + 50 * ofNoise(ofGetElapsedTimef()*0.1, i/200.0)));
    }
//    movingPlane = ofVec3f(400*ofNoise(12+ofGetElapsedTimef()*SPEED)-200,
//                          400*ofNoise(15+ofGetElapsedTimef()*SPEED)-200,
//                          400*ofNoise(17+ofGetElapsedTimef()*SPEED)-200);
//    movingPlaneNormal = ofVec3f(400*ofNoise(32+ofGetElapsedTimef()*SPEED)-200,
//                                400*ofNoise(35+ofGetElapsedTimef()*SPEED)-200,
//                                400*ofNoise(37+ofGetElapsedTimef()*SPEED)-200);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofClear(0);
    ofSetLineWidth(1);
    
    cam.begin();
    ofDrawAxis(20);
    
    ofSetColor(255, 10);
   // for(int i = 0 ;i < NUM_CONES; i++)
     //   conics[i].draw();

    ofSetColor(255,255,255);
    plane = ofVec3f(0, 0, 0);
    planeNormal = ofVec3f(0, 0, 1);
    for(int i = 0 ;i < NUM_CONES; i++)
        conics[i].drawIntersectionsWithPlane(plane, planeNormal);

//    ofSetColor(255, 0, 0, 255);
//    for(int i = 0 ;i < NUM_CONES; i++)
//        conics[i].drawIntersectionsWithPlane(movingPlane, movingPlaneNormal);

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
