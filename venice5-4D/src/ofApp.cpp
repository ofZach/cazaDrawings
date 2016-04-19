#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    for(int i = 0; i < NUM_POLY; i++)
        polychron[i].loadVefFile("16cell.ascii.txt");
}

float da1 = 0;
float da2 = 0;
float da3 = 0;

//--------------------------------------------------------------
void ofApp::update(){
    float less = 0.7;
    float angle1 = da1;
    float angle2 = da2;
    float angle3 = da3;

    for(int i = 0; i < NUM_POLY; i++){
        polychron[i].rotate4DOnly(angle1, angle2, angle3);
        angle1 *= less;
        angle2 *= less;
        angle3 *= less;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(0);

    ofSetColor(255);
    ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
    
    //cam.lookAt(ofPoint(0,0,0));
    //cam.setPosition(200 + 80 * sin(ofGetElapsedTimef()), 0, 200);
    
    ofPushMatrix();
//    ofTranslate(ofGetWidth()*.5, ofGetHeight()*.5);
    cam.begin();
    ofScale(100, 100, 100);
    for(int i = 0; i < NUM_POLY; i++){
        ofSetColor(255, 255 - 255*i/(NUM_POLY+2));
        polychron[i].drawWireframe();
    }
    cam.end();
//    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_RIGHT)
        da3 = 0.01;
    else if(key == OF_KEY_LEFT)
        da3 = -0.01;
    if(key == OF_KEY_UP)
        da2 = 0.01;
    else if(key == OF_KEY_DOWN)
        da2 = -0.01;
    if(key == '[')
        da1 = 0.01;
    else if(key == ']')
        da1 = -0.01;
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == '[' || key == ']')
        da1 = 0;
    if(key == OF_KEY_UP || key == OF_KEY_DOWN)
        da2 = 0;
    if(key == OF_KEY_RIGHT || key == OF_KEY_LEFT)
        da3 = 0;
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

    cout << dragInfo.files[0] << endl;
    for(int i = 0; i < NUM_POLY; i++)
        polychron[i].loadVefFile(dragInfo.files[0]);

}
