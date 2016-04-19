#include "ofApp.h"

#define SLIDER_BOUNDS 20

//--------------------------------------------------------------
void ofApp::setup(){
    
    gui.setup();
    gui.add( COLUMN.setup("Column Width", 200, 50, 550) );
    gui.add( ROW.setup("Row Height", 170, 50, 550) );
    gui.add( diagonals.setup("diagonal", true) );
    gui.add( wave.setup("ANIMATE:", 1, 0, 1) );
    gui.add( columnA.setup(" -Column A", .3, 0.001, 1) );
    gui.add( columnB.setup(" -Column B", .1, 0.001, 1) );
    gui.add( columnC.setup(" -Column C", .06, 0.001, 1) );
    gui.add( rowA.setup(" -Row A", .3, 0.001, 1) );
    gui.add( rowB.setup(" -Row B", .2, 0.001, 1) );
    gui.add( rowC.setup(" -Row C", .06, 0.001, 1) );
    
    columnA.addListener(this, &ofApp::guiUpdate);
    columnB.addListener(this, &ofApp::guiUpdate);
    columnC.addListener(this, &ofApp::guiUpdate);
    rowA.addListener(this, &ofApp::guiUpdate);
    rowB.addListener(this, &ofApp::guiUpdate);
    rowC.addListener(this, &ofApp::guiUpdate);
    
    centerX = ofGetWidth() * .5;
    centerY = ofGetHeight() * .5;
    
    float nullValue;
    guiUpdate(nullValue);
}

void ofApp::update(){
//    COLUMN = 50 + 500*ofNoise( ofGetElapsedTimef()*.3, 1);
//    ROW =  50 + 500*ofNoise( ofGetElapsedTimef()*.3, 5);
    
    float SPEED = 0.5;
    columnA = ofNoise( ofGetElapsedTimef()*SPEED, 2 * wave);
    columnB = ofNoise( ofGetElapsedTimef()*SPEED, 4 * wave);
    columnC = ofNoise( ofGetElapsedTimef()*SPEED, 6 * wave);

    rowA = ofNoise( ofGetElapsedTimef()*SPEED, 8 * wave);
    rowB = ofNoise( ofGetElapsedTimef()*SPEED, 10 * wave);
    rowC = ofNoise( ofGetElapsedTimef()*SPEED, 12 * wave);
}
void ofApp::draw(){
    ofClear(255);
    int j = 0;
    float yPos = 0;
    while(yPos < ofGetHeight()){
        float nextYPos = yPos + rows[j%3];
        int i = 0;
        float xPos = 0;
        while(xPos < ofGetWidth()){
            float nextXPos = xPos + columns[i%4];
            drawQuad(xPos, yPos,
                     nextXPos, yPos,
                     nextXPos, nextYPos,
                     xPos, nextYPos);

            xPos = nextXPos;
            i++;
        }
        yPos = nextYPos;
        j++;
    }
    
// GUI
    gui.draw();
}

void ofApp::drawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4){
    ofSetColor(200);
    ofDrawLine((x1+x2)*.5, (y1+y2)*.5, (x3+x4)*.5, (y3+y4)*.5);
    ofDrawLine((x2+x3)*.5, (y2+y3)*.5, (x4+x1)*.5, (y4+y1)*.5);

    if(!diagonals){
        ofSetColor(0);
        ofDrawLine(x1, y1, x2, y2);
        ofDrawLine(x2, y2, x3, y3);
        ofDrawLine(x3, y3, x4, y4);
        ofDrawLine(x4, y4, x1, y1);
    }
    if(diagonals){
        ofSetColor(200);
        ofDrawLine(x1, y1, x2, y2);
        ofDrawLine(x2, y2, x3, y3);
        ofDrawLine(x3, y3, x4, y4);
        ofDrawLine(x4, y4, x1, y1);
        ofSetColor(0);
        ofDrawLine((x1+x2)*.5, (y1+y2)*.5, (x2+x3)*.5, (y2+y3)*.5);
        ofDrawLine((x2+x3)*.5, (y2+y3)*.5, (x3+x4)*.5, (y3+y4)*.5);
        ofDrawLine((x3+x4)*.5, (y3+y4)*.5, (x4+x1)*.5, (y4+y1)*.5);
        ofDrawLine((x4+x1)*.5, (y4+y1)*.5, (x1+x2)*.5, (y1+y2)*.5);
    }
}

void ofApp::guiUpdate(float &newValue){
    // column b appears twice
    float columnSum = columnA + columnB*2 + columnC;
    float rowSum = rowA + rowB + rowC;
    
    columns[0] = (columnA/columnSum) * COLUMN;
    columns[1] = (columnB/columnSum) * COLUMN;
    columns[2] = (columnC/columnSum) * COLUMN;
    columns[3] = (columnB/columnSum) * COLUMN;
    
    rows[0] = (rowA/rowSum) * ROW;
    rows[1] = (rowB/rowSum) * ROW;
    rows[2] = (rowC/rowSum) * ROW;
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
