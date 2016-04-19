#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    ofSetColor(0);
    
    svg.load("four.svg");
    for (int i = 0; i < svg.getNumPath(); i++){
        ofPath p = svg.getPathAt(i);
        // svg defaults to non zero winding which doesn't look so good as contours
        p.setPolyWindingMode(OF_POLY_WINDING_ODD);
        vector<ofPolyline>& lines = const_cast<vector<ofPolyline>&>(p.getOutline());
        for(int j=0;j<(int)lines.size();j++){
            outlines.push_back(lines[j].getResampledBySpacing(1));
        }
    }
    stepVel = 0.01;
}

//--------------------------------------------------------------
void ofApp::update(){

    float xDiff = fabs(ofGetMouseX() - ofGetPreviousMouseX());
    float yDiff = fabs(ofGetMouseY() - ofGetPreviousMouseY());
    float v = sqrt(powf(xDiff, 2) + powf(yDiff, 2));
    float temp = 1.0 - v*.01;
    if(temp < 0)
        temp = 0;
    if(temp < 0.9){
        
        // shed some lines
        int i = ofRandom(svg.getNumPath());
        ofPath p = svg.getPathAt(i);
        // svg defaults to non zero winding which doesn't look so good as contours
        p.setPolyWindingMode(OF_POLY_WINDING_ODD);
        vector<ofPolyline>& line = const_cast<vector<ofPolyline>&>(p.getOutline());
        fallingLines.push_back(line[0].getResampledBySpacing(1));
        positions.push_back(ofVec2f(ofGetMouseX(), ofGetMouseY()));
        velocities.push_back(ofVec2f(ofRandom(-5, 5) , 0));
        rotations.push_back(0);
        rotationVelocities.push_back(ofRandom(-5, 5));
    }
    if(step > temp){
        step = temp;
        stepVel = .0001;
    }
    stepVel *= 1.3;
    
    step += stepVel;
    if(step > 1)
        step = 1;
    
    temp+=0.05;
    if(temp > 1) temp = 1;
    
    for(int i =0; i < fallingLines.size(); i++){
        velocities[i].y += .2;
        positions[i].x += velocities[i].x;
        positions[i].y += velocities[i].y;
        rotations[i] += rotationVelocities[i];
    }
    
    /////////////////////////////
    // BIG TODO
    //   there is no garbage collecting rn
    
    // remove max one / loop
//    int i = 0;
//    int found = 0;
//    while(!found && i < fallingLines.size()){
//        if(positions[i].y > ofGetHeight() * 1.5){
//            fallingLines.erase(i);
//            positions.erase(i);
//            velocities.erase(i);
//            rotations.erase(i);
//            rotationVelocities.erase(i);
//            found = 1;
//        }
//        i++;
//    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapString(ofToString(stepVel), 20, 20);//ofToString(ofGetFrameRate()),20,20);
    ofPushMatrix();
    ofTranslate(ofGetMouseX(), ofGetMouseY());
//    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
//    ofRotate(mouseX);
    float scale = ofGetHeight() * .003;
    ofScale(scale, scale, scale);
    ofTranslate(-75, -75);
    ofNoFill();
    for (int i = 0; i < (int)outlines.size(); i++){
        ofPolyline & line = outlines[i];
        
        int num = step * line.size();
        
        ofBeginShape();
        for (int j = 0; j < num; j++){
            ofVertex(line[j]);
        }
        ofEndShape();
    }


    ofPopMatrix();
    
    ofPushMatrix();
    //    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    //    ofRotate(mouseX);
    ofNoFill();
    for (int i = 0; i < (int)fallingLines.size(); i++){
        ofPushMatrix();
        ofPolyline & line = fallingLines[i];
        ofTranslate(positions[i].x, positions[i].y);
        ofScale(scale, scale, scale);
        ofRotate(rotations[i]);
        ofTranslate(-75, -75);

        ofBeginShape();
        for (int j = 0; j < line.size(); j++){
            ofVertex(line[j]);
        }
        ofEndShape();
        ofPopMatrix();
    }

    ofPopMatrix();
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
