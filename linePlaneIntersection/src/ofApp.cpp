#include "ofApp.h"

ofVec3f ofApp::crossProduct(ofVec3f a, ofVec3f b){
    float x = a[1] * b[2] - a[2] * b[1];
    float y = a[2] * b[0] - a[0] * b[2];
    float z = a[0] * b[1] - a[1] * b[0];
    return(ofVec3f(x, y, z));
}

float ofApp::dotProduct(ofVec3f a, ofVec3f b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

bool ofApp::linePlaneIntersect(ofVec3f *intersection, ofVec3f linePt1, ofVec3f linePt2, ofVec3f planePt, ofVec3f planeN){
    // line is defined by 2 points on a line
    // plane is defined by planeP point in the plane with normal planeN
    
    ofVec3f l = (linePt2 - linePt1);
    
    float numerator = dotProduct(planeN, (planePt - linePt1) );
    float denominator = dotProduct(planeN, l);
    if(denominator != 0){
        float u = numerator / denominator;
        // BONUS : if u is between 0 and 1, the intersection point is between P1 and P2
        *intersection = l * u;
        return true;
    }
    return false;
}

//--------------------------------------------------------------
void ofApp::setup(){
    
    p1 = ofVec3f(0, 0, 0);
    p2 = ofVec3f(1, 5, 1.66666);
    
    plane = ofVec3f(0, 10, 0);
    planeNormal = ofVec3f(0, 11, 0);
    
    ofVec3f intersect;
    if(linePlaneIntersect(&intersect, p1, p2, plane, planeNormal)){
        printf("%f, %f, %f\n", intersect.x, intersect.y, intersect.z);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    p2 = ofVec3f( 20 * ofNoise(ofGetElapsedTimef()*.1) - 10, 5,  20 * ofNoise(10+ofGetElapsedTimef()*.1)-10 );


}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(0);
    ofSetColor(255);

    cam.begin();
    ofScale(20, 20, 20);
    ofNoFill();
    ofDrawLine(p1, p2);
    ofVec3f intersect;
    if(linePlaneIntersect(&intersect, p1, p2, plane, planeNormal)){
        ofDrawSphere(intersect, .1);
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
