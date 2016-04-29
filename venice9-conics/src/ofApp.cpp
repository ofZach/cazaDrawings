#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    conics[0].setRadius(40);
    conics[1].setRadius(40);
    conics[2].setRadius(160);

    conics[0].setPosition( ofVec3f(-80, 0, 0) );
    conics[0].setLookAt( ofVec3f(-80, 0, 1) );

    conics[1].setPosition( ofVec3f(80, 0, 0) );
    conics[1].setLookAt( ofVec3f(80, 0, 1) );

    conics[2].setPosition( ofVec3f(0, 140, 140) );
    conics[2].setLookAt( ofVec3f(0, 140, 141) );
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofClear(0);
    ofSetLineWidth(1);
    
    cam.begin();
    ofTranslate(0, 300, 0);
    ofRotate(90, 1, 0, 0);
    ofScale(2, 2, 2);
//    ofDrawAxis(20);

    if(showCones){
        ofSetColor(255, 10);
        for(int i = 0 ;i < NUM_CONES; i++)
            conics[i].draw();
    }
    
    static float PHI_ANGLE = 0.618 * M_PI;

    ofSetColor(255, 80);

    for(int i = 0; i < NUM_PLANES; i++){
        
        plane = ofVec3f(100 * cosf(ofGetElapsedTimef() * .4 + i*3),
                        100 * sinf(ofGetElapsedTimef() * .5 + i*3),
                        100 - 80*powf(cosf(ofGetElapsedTimef() + i*.1), 4) );
        planeNormal = ofVec3f(120*cosf(ofGetElapsedTimef() + i*.2),
                              120*sinf(ofGetElapsedTimef() + i*.3),
                              170 + 70*cosf(ofGetElapsedTimef() + i*.4) );
        
        conics[0].fillIntersectionsWithPlane(plane, planeNormal);
        conics[1].fillIntersectionsWithPlane(plane, planeNormal);
        conics[2].fillIntersectionsWithPlane(plane, planeNormal);
    }

    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'c')
        showCones = !showCones;
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
