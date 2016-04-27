#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    for(int i = 0; i < NUM_POLY; i++){
        polychron[i].loadVefFile("8cell.ascii.txt");
    }

//    circleResolution.addListener(this, &ofApp::circleResolutionChanged);
//    ringButton.addListener(this, &ofApp::ringButtonPressed);
    
    gui.setup();
//    gui.add(label1.setup("Label");
//    gui.add(compression.setup("compression", true));
//    polyGroup.setName("Hypercubes");
    gui.add(numPoly.setup("how many?", 6, 1, NUM_POLY));
    gui.add(radiusScale.setup("radius scale", 0, 0, 1));
    gui.add(angleOffset.setup("angle offset", ofVec3f(0, 0, 0), ofVec3f(0, 0, 0),  ofVec3f(180, 180, 180) ));
    gui.add(zoom.setup("nothing", 1, .1, 10));
    gui.add(fourD.setup("4th dimension", ofVec3f(0, 0, 0), ofVec3f(-90, -90, -90),  ofVec3f(90, 90, 90) ));
    gui.add(compression.setup("compression", ofVec3f(1, 1, 1), ofVec3f(.1, .1, .1),  ofVec3f(10, 10, 10) ));
//    sceneGroup.setName("Scene");
    gui.add(autoCamera.setup("camera animated", false));
    gui.add(cameraDistance.setup("anim cam dist", 100, 1, 1000));
//    gui.add(polyGroup);
//    gui.add(sceneGroup);
//    gui.add(center.setup("center", ofVec2f(ofGetWidth()*.5, ofGetHeight()*.5), ofVec2f(0, 0), ofVec2f(ofGetWidth(), ofGetHeight())));
//    gui.add(color.setup("color", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    
    for(int i = 0; i < NUM_POLY; i++){
        rotations[i].x = ofRandom(.01, 0.3);
        rotations[i].y = ofRandom(.01, 0.3);
        rotations[i].z = ofRandom(.01, 0.3);
    }
    // build matrices    
//    for(int i = 0 ;i < NUM_POLY; i++){
//        polyMatrix[i] = ofMatrix4x4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
//        polyMatrix[i].scale(100, 100, 100);
//        // add some rotations and scales between polychrons and increasingly scale them up
//        polyMatrix[i].translate(i*0.1, i*0, 0);
//        polyMatrix[i].rotate(i*45, 1, 0, 0);
//        polyMatrix[i].rotate((i%2)*90, 0, 1, 0);
//        polyMatrix[i].rotate( (floor(i/2)*45), 0, 0, 1);
//        polyMatrix[i].scale(1+i*0.5, 1+i*0.5, 1+i*0.5);
//    }
}

//--------------------------------------------------------------
void ofApp::update(){
    float SCALE = .0001;
    for(int i = 0; i < numPoly; i++){
        polychron[i].rotate4DOnly(SCALE * (i+1) * fourD->x, SCALE * (i+1) * fourD->y, SCALE * (i+1) * fourD->z);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(0);
    
    gui.draw();
    
    ofSetColor(255);
    ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
    
    cam.begin();

    if(autoCamera){
        float camSpeed = .1;
        cam.lookAt(ofPoint(0,0,0));
        cam.setPosition(cameraDistance * sin(ofGetElapsedTimef()*camSpeed), cameraDistance * cosf(ofGetElapsedTimef()*camSpeed), 100);
    }
    
    ofScale(100, 100, 100);
    
    for(int i = 0; i < numPoly; i++){
        ofPushMatrix();
        ofScale(1 + radiusScale * i, 1 + radiusScale * i, 1 + radiusScale * i);
        ofRotate(i * angleOffset->x, 1, 0, 0);
        ofRotate(i * angleOffset->y, 0, 1, 0);
        ofRotate(i * angleOffset->z, 0, 0, 1);
//        ofMultMatrix(polyMatrix[i]);
        ofSetColor(255, 50);
        polychron[i].drawWireframe();
        
        ofPopMatrix();
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
