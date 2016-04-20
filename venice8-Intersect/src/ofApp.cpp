#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    conics.topConeHidden = true;
    
    planeMouseOffset = ofPoint(0, -50, 0);
}

//--------------------------------------------------------------
void ofApp::update(){
}


static int MAX = 1;
//--------------------------------------------------------------
void ofApp::draw(){
    
    
//    cam.lookAt(ofPoint(0,0,0));
//    cam.setPosition(200 + 200 * sin(ofGetElapsedTimef()), 0, 400);
    
    ofClear(255);
 

    cam.begin();
    ofPushMatrix();
//    ofRotateX(ofGetElapsedTimef()*3);
    ofScale(2.5, 2.5, 2.5);

    
    // move camera matrix
    //ofTranslate(ofGetWidth()*.5, ofGetHeight()*.5);
    //    ofRotateX(180*ofNoise(ofGetElapsedTimef()*.1));
    //    ofRotateZ(180*ofNoise(ofGetElapsedTimef()*.1 + 10));
    
    
    // shapes and stuff matrix
    
    ofSetColor(240);
    conics.drawCones();

    ofEnableDepthTest();

    vector <ofxRay::Plane> planes;
    
    float normalAmount = sin(ofGetElapsedTimef() * 0.8) * 0.5 + 0.5;
    for(int z = 0; z < MAX; z++){
        
        ofxRay::Plane plane;
        plane.setInfinite(true);
        plane.setScale(ofVec2f(100, 100));
//        plane.color = ofColor(128, 128, 128);        
        plane.setCenter(planeMouseOffset + ofVec3f(0, 100*ofNoise(ofGetElapsedTimef()*.4)-50 + z*1, 0));
        plane.setNormal(planeMouseOffset + ofVec3f(200 * ofNoise(ofGetElapsedTimef() * .4 + 10)-100,  normalAmount*cos(z+ofGetElapsedTimef()) * 100, normalAmount*sin(z) * 100 + 200 * ofNoise(ofGetElapsedTimef()*.4 + 20)-100 ));

        planes.push_back(plane);
    }
    
    ofSetColor(0, 50);
    ofSetLineWidth(2);
    conics.drawIntersectionFills(planes);
 
    
    ofPopMatrix();

    ofDisableDepthTest();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 't')
        conics.topConeHidden = !conics.topConeHidden;
    if(key == 'b')
        conics.bottomConeHidden = !conics.bottomConeHidden;
    if(key == 'm'){
        if(MAX == 1)
            MAX = 3;
        else
            MAX = 1;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    float dy = y - ofGetPreviousMouseY();
    planeMouseOffset.y += dy;
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
