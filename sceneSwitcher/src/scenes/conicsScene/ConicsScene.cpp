#include "ConicsScene.h"

//--------------------------------------------------------------

void ConicsScene::setup(){
    for(int i = 0; i < NUM_CONES; i++){
        conics[i].setRadius(50 + i);
    }
//    for(int i = 0; i < NUM_CONES; i++){
//        conics[i].setRadius(40 + 4*i);
//        conics[i].setPosition( ofVec3f(0, 0, 0) );
//        conics[i].setLookAt( ofVec3f(0, 0, 1) );
//    }
//    
//    gui.setup();
//    gui.add(numCones.setup("number of cones", 32, 1, 64));
//    //    gui.add(indexed.setup("changes index based", false));
//    
//    gui.add(planeXYTilt.setup("TILT (x y)", 15, -100, 100));
//    gui.add(planeXYTiltPeriod.setup("   - animate", 0, 0, 1));
//    gui.add(planeXYTiltPhase.setup("   - phase", 0, 0, 1));
//    gui.add(planeZTilt.setup("TILT (z)", 50, 1, 100));
//    gui.add(planeZTiltPeriod.setup("   - animate", 0, 0, 1));
//    gui.add(planeZTiltPhase.setup("   - phase", 0, 0, 1));
//    
//    
//    gui.add(planeXY.setup("POSITION (x y)", 50, 0, 100));
//    gui.add(planeXYPeriod.setup("   - animate", 0, 0, 1));
//    gui.add(planeXYPhase.setup("   - phase", 0, 0, 1));
//    gui.add(planeZ.setup("POSITION (z)", 50, 0, 100));
//    gui.add(planeZPeriod.setup("   - animate", 0, 0, 1));
//    gui.add(planeZPhase.setup("   - phase", 0, 0, 1));
//    
//    gui.add(coneAnimate.setup("animate cones", false));
//    gui.add(coneLookPeriod.setup("   - animate", 0, 0, 1));
//    gui.add(coneLookPhase.setup("   - phase", 0, 0, 1));
//    
//    gui.add(coneMagnitude.setup("CONE (x y)", 50, 0, 100));
//    gui.add(conePeriod.setup("   - animate", 0, 0, 1));
//    gui.add(conePhase.setup("   - phase", 0, 0, 1));
//    gui.add(coneZMagnitude.setup("CONE (z)", 50, 0, 100));
//    gui.add(coneZPeriod.setup("   - animate", 0, 0, 1));
//    gui.add(coneZPhase.setup("   - phase", 0, 0, 1));
}

//--------------------------------------------------------------
void ConicsScene::update(){
    float SPEED = .2;
    float diff = .3 * sinf(ofGetElapsedTimef()*.2);
    for(int i = 0 ;i < NUM_CONES; i++){
        conics[i].setPosition( ofPoint(i * 10,0, 200 + 190 * sin(ofGetElapsedTimef() + i/100.0)));
        //conics[i].setHeight(300 + 250 * sinf(2*i+ofGetElapsedTimef()));
        conics[i].setRadius(ofGetMouseX() + (ofGetMouseX()*0.9) * ofSignedNoise(ofGetElapsedTimef()*.3, i/10.0));
        
        conics[i].setLookAt( ofPoint(200 + 100 * sin(ofGetElapsedTimef() + i/100.0), 0 + 50 * ofNoise(ofGetElapsedTimef()*0.1, i/200.0)));
    }
    
}

//--------------------------------------------------------------
void ConicsScene::draw(){
    
    ofClear(0);
    
//    gui.draw();
    
    ofSetLineWidth(1);
    
    cam.begin();
    ofScale(2, 2, 2);
    
    //    ofDrawAxis(20);
    
    //    ofSetColor(255, 10);
    //    for(int i = 0 ;i < NUM_CONES; i++)
    //        conics[i].draw();
    
    plane = ofVec3f(0, 0, 0);
    planeNormal = ofVec3f(0, 0, 1);
    for(int i = 0 ;i < NUM_CONES; i++)
        conics[i].drawIntersectionsWithPlane(plane, planeNormal);
    
    //    ofSetColor(255, 0, 0, 255);
    //    for(int i = 0 ;i < NUM_CONES; i++)
    //        conics[i].drawIntersectionsWithPlane(movingPlane, movingPlaneNormal);
        
//    for(int i = 0 ;i < numCones; i++){
//        if(coneAnimate){
//            conics[i].setLookAt( ofVec3f(cosf(ofGetElapsedTimef()*coneLookPeriod + i*coneLookPhase),
//                                         sinf(ofGetElapsedTimef()*coneLookPeriod + i*coneLookPhase),
//                                         1) );
//            conics[i].setPosition( ofVec3f(coneMagnitude * cosf(ofGetElapsedTimef()*conePeriod + i*conePhase),
//                                           coneMagnitude * sinf(ofGetElapsedTimef()*conePeriod + i*conePhase),
//                                           coneZMagnitude * sinf(ofGetElapsedTimef()*coneZPeriod + i*coneZPhase)) );
//        }
//        plane = ofVec3f(planeXY*cosf(ofGetElapsedTimef()*planeXYPeriod + i*planeXYPhase),
//                        planeXY*sinf(ofGetElapsedTimef()*planeXYPeriod + i*planeXYPhase),
//                        planeZ + (planeZ*.9) * sinf(ofGetElapsedTimef()*planeZPeriod + i*planeZPhase) );
//        
//        planeNormal = ofVec3f(planeXYTilt * cosf(ofGetElapsedTimef()*planeXYTiltPeriod+i*planeXYTiltPhase),
//                              planeXYTilt * sinf(ofGetElapsedTimef()*planeXYTiltPeriod+i*planeXYTiltPhase),
//                              planeZTilt+ (planeZTilt*.9) * sinf(ofGetElapsedTimef()*planeZTiltPeriod + i*planeZTiltPhase) );
//        
//        conics[i].drawIntersectionsWithPlane(plane, planeNormal);
//    }
    
    cam.end();
}