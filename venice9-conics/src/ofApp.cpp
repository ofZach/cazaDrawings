#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    for(int i = 0; i < NUM_CONES; i++){
        conics[i].setRadius(40 + 4*i);
        conics[i].setPosition( ofVec3f(0, 0, 0) );
        conics[i].setLookAt( ofVec3f(0, 0, 1) );
    }
    
    gui.setup();
    gui.add(numCones.setup("number of cones", 32, 1, 64));
//    gui.add(indexed.setup("changes index based", false));
    
    gui.add(planeXYTilt.setup("TILT (x y)", 15, -100, 100));
    gui.add(planeXYTiltPeriod.setup("   - animate", 0, 0, 1));
    gui.add(planeXYTiltPhase.setup("   - phase", 0, 0, 1));
    gui.add(planeZTilt.setup("TILT (z)", 50, 1, 100));
    gui.add(planeZTiltPeriod.setup("   - animate", 0, 0, 1));
    gui.add(planeZTiltPhase.setup("   - phase", 0, 0, 1));

    
    gui.add(planeXY.setup("POSITION (x y)", 50, 0, 100));
    gui.add(planeXYPeriod.setup("   - animate", 0, 0, 1));
    gui.add(planeXYPhase.setup("   - phase", 0, 0, 1));
    gui.add(planeZ.setup("POSITION (z)", 50, 0, 100));
    gui.add(planeZPeriod.setup("   - animate", 0, 0, 1));
    gui.add(planeZPhase.setup("   - phase", 0, 0, 1));

    gui.add(coneAnimate.setup("animate cones", false));
    gui.add(coneLookPeriod.setup("   - animate", 0, 0, 1));
    gui.add(coneLookPhase.setup("   - phase", 0, 0, 1));

    gui.add(coneMagnitude.setup("CONE (x y)", 50, 0, 100));
    gui.add(conePeriod.setup("   - animate", 0, 0, 1));
    gui.add(conePhase.setup("   - phase", 0, 0, 1));
    gui.add(coneZMagnitude.setup("CONE (z)", 50, 0, 100));
    gui.add(coneZPeriod.setup("   - animate", 0, 0, 1));
    gui.add(coneZPhase.setup("   - phase", 0, 0, 1));

    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofClear(0);
    
    gui.draw();
    
    ofSetLineWidth(1);
    
    cam.begin();
    ofScale(2, 2, 2);
    
//    ofDrawAxis(20);
    
//    ofSetColor(255, 10);
//    for(int i = 0 ;i < NUM_CONES; i++)
//        conics[i].draw();
    
    ofSetColor(255, 255);
    
    for(int i = 0 ;i < numCones; i++){
        if(coneAnimate){
            conics[i].setLookAt( ofVec3f(cosf(ofGetElapsedTimef()*coneLookPeriod + i*coneLookPhase),
                                         sinf(ofGetElapsedTimef()*coneLookPeriod + i*coneLookPhase),
                                         1) );
            conics[i].setPosition( ofVec3f(coneMagnitude * cosf(ofGetElapsedTimef()*conePeriod + i*conePhase),
                                           coneMagnitude * sinf(ofGetElapsedTimef()*conePeriod + i*conePhase),
                                           coneZMagnitude * sinf(ofGetElapsedTimef()*coneZPeriod + i*coneZPhase)) );
        }
        plane = ofVec3f(planeXY*cosf(ofGetElapsedTimef()*planeXYPeriod + i*planeXYPhase),
                        planeXY*sinf(ofGetElapsedTimef()*planeXYPeriod + i*planeXYPhase),
                        planeZ + (planeZ*.9) * sinf(ofGetElapsedTimef()*planeZPeriod + i*planeZPhase) );

        planeNormal = ofVec3f(planeXYTilt * cosf(ofGetElapsedTimef()*planeXYTiltPeriod+i*planeXYTiltPhase),
                              planeXYTilt * sinf(ofGetElapsedTimef()*planeXYTiltPeriod+i*planeXYTiltPhase),
                              planeZTilt+ (planeZTilt*.9) * sinf(ofGetElapsedTimef()*planeZTiltPeriod + i*planeZTiltPhase) );
        
        conics[i].drawIntersectionsWithPlane(plane, planeNormal);
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
