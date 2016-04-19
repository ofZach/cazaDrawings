#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    for(int i = 0; i < NUM_POLY; i++)
        polychron[i].loadVefFile("120cell.ascii.txt");
    
    for(int i = 0; i < polychron[0].getNumVertices(); i++){
        visitedNodeCount.push_back(0);
    }
}

float da1 = 0;
float da2 = 0;
float da3 = 0;
int highlightedCounter = 0;
int MAX_STEPS = 100;

//--------------------------------------------------------------
void ofApp::update(){
    static int fireTimer = 0;
    static int FIRE_DUR = 2000;
    
    if(floor(ofGetElapsedTimeMillis()) > fireTimer+ FIRE_DUR){
        fireTimer = ofGetElapsedTimeMillis();
        highlightedCounter = 0;
        highlightedNodes.clear();
        adjacentNodes.clear();
        visitedNodeCount.clear();
        for(int i = 0; i < polychron[0].getNumVertices(); i++){
            visitedNodeCount.push_back(0);
        }
        unsigned int randIndex = arc4random()%polychron[0].getNumVertices();
        highlightedNodes.push_back(randIndex);
    }
    
    static int countIteration = 0;
    static int ANIM_DUR = 10;
    
    if(floor(ofGetElapsedTimeMillis()) > countIteration+ ANIM_DUR){
        countIteration = ofGetElapsedTimeMillis();
        if(highlightedNodes.size()){
            unsigned int randIndex = arc4random()%highlightedNodes.size();
            adjacentNodes = polychron[0].allVerticesAdjacentTo(highlightedNodes[ randIndex ]);
            // find least visited node
            unsigned int smallestIndex = 0;
            if(adjacentNodes.size() > 1){
                for(int i = 1; i < adjacentNodes.size(); i++){
                    if(visitedNodeCount[ adjacentNodes[i] ] < visitedNodeCount[ adjacentNodes[smallestIndex] ])
                        smallestIndex = i;
                }
            }
//            unsigned int randSelection = arc4random()%adjacentNodes.size();
            highlightedNodes.clear();
            highlightedNodes.push_back(adjacentNodes[smallestIndex]);
            visitedNodeCount[ adjacentNodes[smallestIndex] ]++;
            
            highlightedCounter++;
            if(highlightedCounter > MAX_STEPS){
                adjacentNodes.clear();
                highlightedNodes.clear();
                highlightedCounter = 0;
            }
        }
    }
    
    // KEYBOARD ROTATIONS
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
    
//    ofTranslate(ofGetWidth()*.5, ofGetHeight()*.5);
    cam.begin();

    ofScale(100, 100, 100);
    for(int i = 1; i < 2; i++){//for(int i = 0; i < NUM_POLY; i++){
        ofPushMatrix();
        
        if(i == 1){
            ofTranslate(i*0.1, i*0);
            ofRotateX(i*45);
            ofScale(i*1.5, i*1.5, i*1.5);
        }

        ofSetColor(255, 40);
        polychron[i].drawWireframe();
        ofSetColor(255, 50 - (50.0/MAX_STEPS)*highlightedCounter);
        for(int h = 0; h < adjacentNodes.size(); h++){
            polychron[i].drawEdgesTouchingNode(adjacentNodes[h]);
        }
        ofSetColor(255, 200 - (200.0/MAX_STEPS)*highlightedCounter);
        for(int h = 0; h < highlightedNodes.size(); h++){
            polychron[i].drawEdgesTouchingNode(highlightedNodes[h]);
        }
        
        ofPopMatrix();
    }
    cam.end();
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

//    cout << dragInfo.files[0] << endl;
    for(int i = 0; i < NUM_POLY; i++)
        polychron[i].loadVefFile(dragInfo.files[0]);

    highlightedNodes.clear();
    adjacentNodes.clear();
    visitedNodeCount.clear();
    for(int i = 0; i < polychron[0].getNumVertices(); i++){
        visitedNodeCount.push_back(0);
    }

}
