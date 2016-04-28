#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    for(int i = 0; i < NUM_POLY; i++){
        polychron[i].loadVefFile("8cell.ascii.txt");
    }
    
    gui.setup();
    gui.add(numPoly.setup("how many?", 6, 1, NUM_POLY));
    gui.add(grid.setup("grid", false));
    gui.add(gridGap.setup("grid space", 2.5, 0, 10));
    gui.add(indexed.setup("changes index based", false));
    gui.add(radiusScale.setup("scale", 0, 0, 1));
    gui.add(angleOffset.setup("angle offset", ofVec3f(0, 0, 0), ofVec3f(0, 0, 0),  ofVec3f(180, 180, 180) ));

    gui.add(fourDAnimated.setup("4D animated", false));
    gui.add(fourD.setup("4th dimension, w * _", ofVec3f(0, 0, 0), ofVec3f(-90, -90, -90),  ofVec3f(90, 90, 90) ));
//    gui.add(compression.setup("compression", ofVec3f(0, 0, 0), ofVec3f(-.99, -.99, -.99),  ofVec3f(2, 2, 2) ));
    compression.setup("compression", ofVec3f(0, 0, 0), ofVec3f(-.99, -.99, -.99),  ofVec3f(2, 2, 2) );

    gui.add(rotAnimations.setup("scatter rotation", false));
    gui.add(rotAnimSpeed.setup(" - [speed]", 10, .01, 30));
    gui.add(rotAnimMag.setup(" - [magnitude]", 1, 0, 90));

    gui.add(posAnimations.setup("scatter position", false));
    gui.add(posAnimSpeed.setup(" - [speed]", 1, .01, 30));
    gui.add(posAnimMag.setup(" - [magnitude]", 1, 0, 5));

    gui.add(autoCamera.setup("camera animated", false));
    gui.add(cameraDistance.setup("anim cam dist", 100, 1, 3000));

//    gui.add(color.setup("color", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    
    for(int i = 0; i < NUM_POLY; i++){
        rotations[i].x = ofRandom(.01, 0.3);
        rotations[i].y = ofRandom(.01, 0.3);
        rotations[i].z = ofRandom(.01, 0.3);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    int num;
    if(grid) num = NUM_POLY;
    else num = numPoly;
    

    if(fourDAnimated){
        float SCALE = 0.0001;
        for(int i = 0; i < num; i++){
            if(indexed)
                polychron[i].rotate4DOnly(SCALE * (i+1) * fourD->x, SCALE * (i+1) * fourD->y, SCALE * (i+1) * fourD->z);
            else
                polychron[i].rotate4DOnly(SCALE * fourD->x, SCALE * fourD->y, SCALE * fourD->z);
        }
    }
    else{
        float SCALE = 0.01;
        for(int i = 0; i < num; i++){
            if(indexed)
                polychron[i].rotate4DOnlyOnce(SCALE * (i+1) * fourD->x, SCALE * (i+1) * fourD->y, SCALE * (i+1) * fourD->z);
            else
                polychron[i].rotate4DOnlyOnce(SCALE * fourD->x, SCALE * fourD->y, SCALE * fourD->z);
        }
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
    
    int num;
    if(grid) num = NUM_POLY;
    else num = numPoly;
    for(int i = 0; i < num; i++){
        ofPushMatrix();
        if(grid){
            ofTranslate( gridGap * (i%5 - 2), gridGap * ((int)(i/5.0) - 2), 0);
        }
        if(indexed){
            ofScale(1 + radiusScale * i, 1 + radiusScale * i, 1 + radiusScale * i);
            ofScale(1 + compression->x * (i+1), 1 + compression->y * (i+1), 1 + compression->z * (i+1));
            ofRotate(i * angleOffset->x, 1, 0, 0);
            ofRotate(i * angleOffset->y, 0, 1, 0);
            ofRotate(i * angleOffset->z, 0, 0, 1);
        }
        else{
            ofScale(1 + radiusScale, 1 + radiusScale, 1 + radiusScale);
            ofScale(1 + compression->x, 1 + compression->y, 1 + compression->z);
            ofRotate(angleOffset->x, 1, 0, 0);
            ofRotate(angleOffset->y, 0, 1, 0);
            ofRotate(angleOffset->z, 0, 0, 1);
        }
//        ofMultMatrix(polyMatrix[i]);
        if(posAnimations){
            ofTranslate(posAnimMag * sinf(ofGetElapsedTimef()*rotations[i].x * posAnimSpeed),
                        posAnimMag * sinf(ofGetElapsedTimef()*rotations[i].y * posAnimSpeed),
                        posAnimMag * sinf(ofGetElapsedTimef()*rotations[i].z * posAnimSpeed) );
        }
        if(rotAnimations){
            ofRotate(rotAnimMag * sinf(ofGetElapsedTimef()*rotations[i].x * rotAnimSpeed), 1, 0, 0);
            ofRotate(rotAnimMag * sinf(ofGetElapsedTimef()*rotations[i].y * rotAnimSpeed), 0, 1, 0);
            ofRotate(rotAnimMag * sinf(ofGetElapsedTimef()*rotations[i].z * rotAnimSpeed), 0, 0, 1);
        }
        ofSetColor(255, 90);
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
