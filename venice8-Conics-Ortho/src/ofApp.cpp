#include "ofApp.h"

#define NUM_CONES 12

//--------------------------------------------------------------
void ofApp::setup(){

    for(int i = 0; i < NUM_CONES; i++){
        ConicSections conic = ConicSections(100, 5+powf(i, 2));
        conic.topConeHidden = true;
        conics.push_back(conic);
    }
    
    planeMouseOffset = ofPoint(0, -10, 0);
}

//--------------------------------------------------------------
void ofApp::update(){

}

ofQuaternion ofApp::convert(ofMatrix4x4 m1) {
    double w = sqrt(1.0 + m1._mat[0].x + m1._mat[1].y + m1._mat[2].z) / 2.0;
    double w4 = (4.0 * w);
    double x = (m1._mat[2].y - m1._mat[1].z) / w4 ;
    double y = (m1._mat[0].z - m1._mat[2].x) / w4 ;
    double z = (m1._mat[1].x - m1._mat[0].y) / w4 ;
    return ofQuaternion(x, y, z, w);
//    w = sqrt(1.0 + m1.m00 + m1.m11 + m1.m22) / 2.0;
//    double w4 = (4.0 * w);
//    x = (m1.m21 - m1.m12) / w4 ;
//    y = (m1.m02 - m1.m20) / w4 ;
//    z = (m1.m10 - m1.m01) / w4 ;
}

//--------------------------------------------------------------
void ofApp::draw(){
    

    ofClear(255);
 

    cam.begin();
    ofPushMatrix();
//    ofRotateX(ofGetElapsedTimef()*3);
    ofScale(2.5, 2.5, 2.5);

    ofSetColor(0, 5);
    for(int i = 0; i < NUM_CONES; i++)
        conics[i].drawCones();

//    ofEnableDepthTest();

    vector <ofxRay::Plane> planes;
    
    float normalAmount = sin(ofGetElapsedTimef() * 0.8) * 0.5 + 0.5;
    for(int z = 0; z < 1; z++){
        
        ofxRay::Plane plane;
        plane.setInfinite(true);
        plane.setScale(ofVec2f(100, 100));
//        plane.color = ofColor(128, 128, 128);        
        plane.setCenter(ofVec3f(0, 20*ofNoise(ofGetElapsedTimef()*.4)-50 + z*1, 0));
        plane.setNormal(ofVec3f(200 * ofNoise(ofGetElapsedTimef() * .4 + 10)-100,
                                normalAmount*cos(z+ofGetElapsedTimef()) * 100 + 200,
                                200 * ofNoise(ofGetElapsedTimef()*.4 + 20)-100)  + normalAmount*sin(z) * 100);
        planes.push_back(plane);
    }
    
    static float rot = 0;
    rot = sinf(ofGetElapsedTimef()) * 0.01;
    ofMatrix4x4 m =  ofMatrix4x4(cosf(rot), sinf(rot), 0, 0, -sinf(rot), cosf(rot), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    for(int i = 0; i < 500; i++){
        conics[5].bottomConeRays[i] *= m;
    }

    
    ofSetColor(0, 30);
    ofSetLineWidth(2);

    for(int i = 0; i < NUM_CONES; i++){
        conics[i].drawIntersectionFills(planes);
    }
    
    ofPopMatrix();

//    ofDisableDepthTest();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//    if(key == 't')
//        conics.topConeHidden = !conics.topConeHidden;
//    if(key == 'b')
//        conics.bottomConeHidden = !conics.bottomConeHidden;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
//    float dy = y - ofGetPreviousMouseY();
//    planeMouseOffset.y += dy;
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
