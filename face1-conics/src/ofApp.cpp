#include "ofApp.h"


// mouth: 48,60 (48,54)
// head: 0,67 (3,13)
// eyeL: 36,41 (36,39)
// eyeR: 42,47 (42,45)
// nose: 29,35 (31,35)

// mouth: 51-top-middle, 57-bottom middle

//--------------------------------------------------------------
void ofApp::setup(){
    PL.setup();

    plane = ofVec3f(0, 0, 0);
    planeNormal = ofVec3f(0, 0, 1);
    
    for(int i = 0; i < NUM_CONES; i++)
        mouthCones[i].setRadius(20 + 10*i);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    float diff = sin(ofGetElapsedTimef()*.3);
    float RANGE = 200;
    for(int i = 0 ;i < NUM_CONES; i++){
        mouthCones[i].setPosition( PL.ptData[PL.frame][51] + ofVec3f(RANGE*ofNoise(ofGetElapsedTimef()*.3 + diff*i)-(RANGE*.5),
                                                                 RANGE*ofNoise(10+ofGetElapsedTimef()*.3 + diff*i)-(RANGE*.5),
                                                                 100) );
        mouthCones[i].setLookAt( PL.ptData[PL.frame][57] );
//        conics[i].setHeight(300 + 250 * sinf(2*i+ofGetElapsedTimef()));
//        conics[i].setRadius(100 + 90 * sinf(2*i+ofGetElapsedTimef()*.3));
    }

    PL.update();
}
//--------------------------------------------------------------
void ofApp::draw(){
    
    ofClear(0);

    cam.begin();
    ofRotate(180, 0, 0, 1);
    ofTranslate(-380, -260);
    ofSetColor(255, 64);
    PL.draw();
    
    ofSetColor(255, 255);
    for(int i = 0; i < NUM_CONES; i++)
        mouthCones[i].drawIntersectionsWithPlane(plane, planeNormal);
    
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
