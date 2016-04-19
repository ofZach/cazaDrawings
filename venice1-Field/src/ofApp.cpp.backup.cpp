#include "ofApp.h"

#define SLIDER_BOUNDS 20

//--------------------------------------------------------------
void ofApp::setup(){
    
    gui.setup();
    gui.add( wave.setup("wave", 1, 0, 1) );
    gui.add( diagonals.setup("diagonal", true) );
    gui.add( stretch.setup("stretch",
                           ofVec2f(ofRandom(-SLIDER_BOUNDS, SLIDER_BOUNDS), ofRandom(-SLIDER_BOUNDS, SLIDER_BOUNDS)),
                           ofVec2f(-SLIDER_BOUNDS, -SLIDER_BOUNDS),
                           ofVec2f(SLIDER_BOUNDS, SLIDER_BOUNDS ) ));
    gui.add( skew.setup("skew",
                        ofVec2f(ofRandom(-SLIDER_BOUNDS, SLIDER_BOUNDS), ofRandom(-SLIDER_BOUNDS, SLIDER_BOUNDS)),
                        ofVec2f(-SLIDER_BOUNDS, -SLIDER_BOUNDS),
                        ofVec2f(SLIDER_BOUNDS, SLIDER_BOUNDS ) ));
    
    centerX = ofGetWidth() * .5;
    centerY = ofGetHeight() * .5;
    for(int i = 0; i < COLUMNS; i++){
        for(int j = 0; j < ROWS; j++){
            x[i][j] = centerX + (i-4)*50;
            y[i][j] = centerY + (j-4)*50;
        }
    }
    
}
void ofApp::update(){
    float time = ofGetElapsedTimeMillis() / 300.0;
    for(int i = 0; i < COLUMNS; i++){
        for(int j = 0; j < ROWS; j++){
            float w = wave * (10 * sin(time + i*2) + 10 * sin(time*.333 + j));
            x[i][j] =  j*skew->x + i*stretch->x + (i-4)*50 + w;
            y[i][j] =  i*skew->y + j*stretch->y + (j-4)*50 + w;
        }
    }
}
void ofApp::draw(){
    ofClear(0);
    gui.draw();
    
    /////////////////////////////////
    // draw the grid
    
    centerX = ofGetWidth() * .5 + 100;
    centerY = ofGetHeight() * .5;
    
    if(!diagonals){
        // draw squares
        ofSetColor(64);
        for(int i = 0; i < COLUMNS - 1; i++){
            for(int j = 0; j < ROWS - 1; j++){
                ofDrawLine( centerX + x[i][j],  centerY + y[i][j],
                           centerX + x[i+1][j+1], centerY + y[i+1][j+1] );
                ofDrawLine( centerX + x[i][j+1],  centerY + y[i][j+1],
                           centerX + x[i+1][j], centerY + y[i+1][j] );
            }
        }
        ofSetColor(255);
        for(int i = 0; i < COLUMNS - 1; i++)
            for(int j = 0; j < ROWS; j++)
                ofDrawLine( centerX + x[i][j], centerY + y[i][j],
                           centerX + x[i+1][j], centerY + y[i+1][j] );
        for(int i = 0; i < COLUMNS; i++)
            for(int j = 0; j < ROWS - 1; j++)
                ofDrawLine( centerX + x[i][j], centerY + y[i][j],
                           centerX + x[i][j+1], centerY + y[i][j+1] );
    }
    else {
        // draw diamonds
        ofSetColor(32);
        for(int i = 0; i < COLUMNS - 1; i++){
            for(int j = 0; j < ROWS - 1; j++){
                ofDrawLine( centerX + (x[i][j]+x[i][j+1])*.5, centerY + (y[i][j]+y[i][j+1])*.5,
                           centerX + (x[i+1][j]+x[i+1][j+1])*.5, centerY + (y[i+1][j]+y[i+1][j+1])*.5);
                ofDrawLine( centerX + (x[i][j]+x[i+1][j])*.5, centerY + (y[i][j]+y[i+1][j])*.5,
                           centerX + (x[i][j+1]+x[i+1][j+1])*.5, centerY + (y[i][j+1]+y[i+1][j+1])*.5);
            }
        }
        ofSetColor(64);
        for(int i = 0; i < COLUMNS - 1; i++)
            for(int j = 0; j < ROWS; j++)
                ofDrawLine( centerX + x[i][j], centerY + y[i][j],
                           centerX + x[i+1][j], centerY + y[i+1][j] );
        for(int i = 0; i < COLUMNS; i++)
            for(int j = 0; j < ROWS - 1; j++)
                ofDrawLine( centerX + x[i][j], centerY + y[i][j],
                           centerX + x[i][j+1], centerY + y[i][j+1] );
        
        ofSetColor(255);
        for(int i = 0; i < COLUMNS - 1; i++){
            for(int j = 0; j < ROWS - 1; j++){
                ofDrawLine( centerX + (x[i][j]+x[i+1][j])*.5, centerY + (y[i][j]+y[i+1][j])*.5,
                           centerX + (x[i+1][j]+x[i+1][j+1])*.5, centerY + (y[i+1][j]+y[i+1][j+1])*.5);
                ofDrawLine( centerX + (x[i][j+1]+x[i+1][j+1])*.5, centerY + (y[i][j+1]+y[i+1][j+1])*.5,
                           centerX + (x[i+1][j]+x[i+1][j+1])*.5, centerY + (y[i+1][j]+y[i+1][j+1])*.5);
                ofDrawLine( centerX + (x[i][j+1]+x[i+1][j+1])*.5, centerY + (y[i][j+1]+y[i+1][j+1])*.5,
                           centerX + (x[i][j]+x[i][j+1])*.5, centerY + (y[i][j]+y[i][j+1])*.5);
                ofDrawLine( centerX + (x[i][j]+x[i+1][j])*.5, centerY + (y[i][j]+y[i+1][j])*.5,
                           centerX + (x[i][j]+x[i][j+1])*.5, centerY + (y[i][j]+y[i][j+1])*.5);
            }
        }
    }

    /////////////////////////////////
    // draw the one unit
    
    int i = 0;
    int j = 0;
    centerX = 70;
    centerY = ofGetHeight() * .5;
    
    float pX[2][2];
    float pY[2][2];
    float newScale = 3;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            pX[i][j] =  j*skew->x + i*stretch->x + (i)*50;
            pY[i][j] =  i*skew->y + j*stretch->y + (j)*50;
        }
    }
    
    


    if(!diagonals){
        // draw squares
        ofSetColor(64);
        ofDrawLine( centerX + pX[i][j] * newScale,  centerY + pY[i][j] * newScale,
                   centerX + pX[i+1][j+1] * newScale, centerY + pY[i+1][j+1]  * newScale);
        ofDrawLine( centerX + pX[i][j+1] * newScale,  centerY + pY[i][j+1] * newScale,
                   centerX + pX[i+1][j] * newScale, centerY + pY[i+1][j]  * newScale);
        ofSetColor(255);
        ofDrawLine( centerX + pX[i][j] * newScale, centerY + pY[i][j] * newScale,
                   centerX + pX[i+1][j] * newScale, centerY + pY[i+1][j] * newScale );
        ofDrawLine( centerX + pX[i][j] * newScale, centerY + pY[i][j] * newScale,
                   centerX + pX[i][j+1] * newScale, centerY + pY[i][j+1] * newScale );

        ofDrawLine( centerX + pX[i][j+1] * newScale, centerY + pY[i][j+1] * newScale,
                   centerX + pX[i+1][j+1] * newScale, centerY + pY[i+1][j+1] * newScale );
        ofDrawLine( centerX + pX[i+1][j] * newScale, centerY + pY[i+1][j] * newScale,
                   centerX + pX[i+1][j+1] * newScale, centerY + pY[i+1][j+1] * newScale );
    }
    else {
        // draw diamonds
        ofSetColor(32);
        ofDrawLine( centerX + (pX[i][j]+pX[i][j+1])*.5 * newScale, centerY + (pY[i][j]+pY[i][j+1])*.5 * newScale,
                   centerX + (pX[i+1][j]+pX[i+1][j+1])*.5 * newScale, centerY + (pY[i+1][j]+pY[i+1][j+1])*.5 * newScale);
        ofDrawLine( centerX + (pX[i][j]+pX[i+1][j])*.5 * newScale, centerY + (pY[i][j]+pY[i+1][j])*.5 * newScale,
                   centerX + (pX[i][j+1]+pX[i+1][j+1])*.5 * newScale, centerY + (pY[i][j+1]+pY[i+1][j+1])*.5 * newScale);

        ofSetColor(64);

        ofDrawLine( centerX + pX[i][j] * newScale, centerY + pY[i][j] * newScale,
                   centerX + pX[i+1][j] * newScale, centerY + pY[i+1][j] * newScale );
        ofDrawLine( centerX + pX[i][j] * newScale, centerY + pY[i][j] * newScale,
                   centerX + pX[i][j+1] * newScale, centerY + pY[i][j+1]  * newScale);

        ofDrawLine( centerX + pX[i][j+1] * newScale, centerY + pY[i][j+1] * newScale,
                   centerX + pX[i+1][j+1] * newScale, centerY + pY[i+1][j+1] * newScale );
        ofDrawLine( centerX + pX[i+1][j] * newScale, centerY + pY[i+1][j] * newScale,
                   centerX + pX[i+1][j+1] * newScale, centerY + pY[i+1][j+1]  * newScale);

        ofSetColor(255);
        ofDrawLine( centerX + (pX[i][j]+pX[i+1][j])*.5 * newScale, centerY + (pY[i][j]+pY[i+1][j])*.5 * newScale,
                   centerX + (pX[i+1][j]+pX[i+1][j+1])*.5 * newScale, centerY + (pY[i+1][j]+pY[i+1][j+1])*.5 * newScale);
        ofDrawLine( centerX + (pX[i][j+1]+pX[i+1][j+1])*.5 * newScale, centerY + (pY[i][j+1]+pY[i+1][j+1])*.5 * newScale,
                   centerX + (pX[i+1][j]+pX[i+1][j+1])*.5 * newScale, centerY + (pY[i+1][j]+pY[i+1][j+1])*.5 * newScale);
        ofDrawLine( centerX + (pX[i][j+1]+pX[i+1][j+1])*.5 * newScale, centerY + (pY[i][j+1]+pY[i+1][j+1])*.5 * newScale,
                   centerX + (pX[i][j]+pX[i][j+1])*.5 * newScale, centerY + (pY[i][j]+pY[i][j+1])*.5 * newScale);
        ofDrawLine( centerX + (pX[i][j]+pX[i+1][j])*.5 * newScale, centerY + (pY[i][j]+pY[i+1][j])*.5 * newScale,
                   centerX + (pX[i][j]+pX[i][j+1])*.5 * newScale, centerY + (pY[i][j]+pY[i][j+1])*.5 * newScale);
    }
    
    
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
