#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}


static float angle = 0;
ofEasyCam cam;
ofNode node;
ofNode node2;


//--------------------------------------------------------------
void ofApp::draw(){
    
    

    node.setPosition(0,0,300);
    node.lookAt( (150 + 150 * sin(ofGetElapsedTimef())) * ofPoint(cos(angle),(sin(angle))));
    
    node2.setParent(node);
    node2.setPosition(0,0,50);
    
    angle+= 0.01;

    ofEnableDepthTest();
    
    cam.begin();
    node.draw();
    node2.draw();
    
    ofSetColor(127,127,127);
    ofDrawPlane(300, 300);
    ofDrawAxis(100);
    
    // how you transform:
    node.transformGL();
    ofNoFill();
    ofSetColor(255,255,255);
    ofCircle(ofPoint(0,0,-200), 50);
    node.restoreTransformGL();
    
    // how you get the point in 3d
    for (int i = 0; i < 100; i++){
        float angle = ofMap(i, 0, 100, 0, TWO_PI);
        ofPoint pt = 50 * ofPoint(cos(angle), sin(angle));
        pt.z -= 200;
        
        ofPoint ptTransformed = pt *  node.getLocalTransformMatrix();
        
        ofLine(node.getPosition(), ptTransformed);
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
