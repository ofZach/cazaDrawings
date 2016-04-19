#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    for(int i = 0; i < NUM_POLY; i++){
        polychron[i].loadVefFile("8cell.ascii.txt");
        highlighted[i].clear();
    }
}

float da1 = 0;
float da2 = 0;
float da3 = 0;

//--------------------------------------------------------------
void ofApp::update(){
    
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

ofVec3f ofApp::worldToScreen(ofVec3f WorldXYZ, ofMatrix4x4 additionalTransform) {
    ofRectangle viewport = ofGetCurrentRenderer()->getCurrentViewport();
    
    ofVec3f CameraXYZ = WorldXYZ * additionalTransform * cam.getModelViewProjectionMatrix(viewport);
    ofVec3f ScreenXYZ;
    
    ScreenXYZ.x = (CameraXYZ.x + 1.0f) / 2.0f * viewport.width + viewport.x;
    ScreenXYZ.y = (1.0f - CameraXYZ.y) / 2.0f * viewport.height + viewport.y;
    ScreenXYZ.z = CameraXYZ.z;
    return ScreenXYZ;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(0);

    ofSetColor(255);
    ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
    
    //cam.lookAt(ofPoint(0,0,0));
    //cam.setPosition(200 + 80 * sin(ofGetElapsedTimef()), 0, 200);
    
//    ofTranslate(ofGetWidth()*.5, ofGetHeight()*.5);
    
    ofDrawLine(ofGetWidth()*.5, 0, ofGetWidth()*.5, ofGetHeight());
    
    ofMatrix4x4 polyMatrix;
    
    cam.begin();

    ofPushMatrix();
    ofScale(100, 100, 100);
    for(int i = 0; i < NUM_POLY; i++){
        ofPushMatrix();
        
        polyMatrix = ofMatrix4x4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
        if(i == 1){
            polyMatrix.translate(i*0.1, i*0, 0);
            polyMatrix.rotate(45, 1, 0, 0);
            polyMatrix.scale(1.5, 1.5, 1.5);
        }

        ofSetColor(255, 255);
        ofMultMatrix(polyMatrix);
        polychron[i].drawWireframe();
        
        
        // CALCULATE the highlighted vertices
        for(int i = 0; i < NUM_POLY; i++){
            highlighted[i].clear();
            for(int v = 0; v < polychron[i].getNumVertices(); v++){
                Point4D vertex = polychron[i].vertices[v];
                ofVec3f screenLocation = worldToScreen( ofVec3f(vertex.x, vertex.y, vertex.z), polyMatrix );
                if(screenLocation.x < ofGetWidth()*.5){
                    highlighted[i].push_back(v);
                }
            }
        }
  
        
        // DRAW the highlighted vertices
        ofSetColor(100, 100, 255);
        for(int h = 0; h < highlighted[i].size(); h++){
            ofDrawSphere(polychron[i].vertices[highlighted[i][h]].x,
                         polychron[i].vertices[highlighted[i][h]].y,
                         polychron[i].vertices[highlighted[i][h]].z, .06);
        }
        ofPopMatrix();
    }
    ofPopMatrix();
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
    for(int i = 0; i < NUM_POLY; i++){
        polychron[i].loadVefFile(dragInfo.files[0]);
        highlighted[i].clear();
    }
}
