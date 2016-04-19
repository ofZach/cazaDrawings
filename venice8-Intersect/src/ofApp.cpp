#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    topCone = ofConePrimitive(CONE_RADIUS, -CONE_HEIGHT, CONE_RESOLUTION, 1);
    bottomCone = ofConePrimitive(CONE_RADIUS, CONE_HEIGHT, CONE_RESOLUTION, 1);
    ofMesh m = topCone.getMesh();
    m.getVertices();
    
    // build cones from mesh geometry of cone
//    topConeApex = topCone.getMesh().getVertices()[0];
//    vector<ofPoint> capVertices = topCone.getCapMesh().getVertices();
//    for(int i = 0; i < capVertices.size(); i++){
//        ofxRay::Ray ray;
//        ray.setStart(topConeApex);
//        ray.setEnd(capVertices[i]);
//        rays.push_back(ray);
//    }
    
    ofPoint origin = ofPoint(0, 0, 0);
    for(int i = 0;i < CONE_RESOLUTION; i++){
        ofxRay::Ray ray;
        ray.setStart( origin );
        ray.setEnd(ofPoint(CONE_RADIUS*cosf(2*M_PI*i/CONE_RESOLUTION), CONE_HEIGHT, CONE_RADIUS*sinf(2*M_PI*i/CONE_RESOLUTION)));
        rays.push_back(ray);
    }
    
    plane.setCenter(ofVec3f(0, 0, 0));
    plane.setNormal(ofVec3f(0, 1, 0));
    plane.setInfinite(true);
    plane.setScale(ofVec2f(100, 100));
    plane.color = ofColor(128, 128, 128);

    planeMouseOffset = ofPoint(0, 0, 0);
}

//--------------------------------------------------------------
void ofApp::update(){
    // update position and orientation of the plane
    plane.setCenter(planeMouseOffset + ofVec3f(0, 100*ofNoise(ofGetElapsedTimef()*.4)-50, 0));
    plane.setNormal(planeMouseOffset + ofVec3f(200 * ofNoise(ofGetElapsedTimef() * .4 + 10)-100, 100, 200 * ofNoise(ofGetElapsedTimef()*.4 + 20)-100 ));

    intersections.clear();
    // find all the intersections between the plane and the cones
    for(int i = 0; i < rays.size(); i++){
        ofVec3f intersect;
        if(plane.intersect(rays[i], intersect)){
            intersections.push_back(intersect);
        }
    }
    
    //now take these interesctions and clip them against the top and bottom of the cones
    intersectionLines.clear();
    ofPolyline polyline;
    intersectionLines.push_back(polyline);
    int whichIndex = 0;
    for(int i = 0; i < intersections.size(); i++){
        if(intersections[i].y > -CONE_HEIGHT && intersections[i].y < 0){// -CONE_HEIGHT){
            intersectionLines[whichIndex].addVertex(intersections[i]);
        }
        else if (intersectionLines[whichIndex].getVertices().size() > 0){
            ofPolyline polyline;
            intersectionLines.push_back(polyline);
            whichIndex++;
        }
//        cur.setClosed(true);
    }
}

ofEasyCam cam;

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    cam.lookAt(ofPoint(0,0,0));
    cam.setPosition(200 + 200 * sin(ofGetElapsedTimef()), 0, 400);
    
    ofClear(255);
    
    cam.begin();
    ofPushMatrix();
    ofRotateX(ofGetElapsedTimef()*3);
    // move camera matrix
    //ofTranslate(ofGetWidth()*.5, ofGetHeight()*.5);
    //    ofRotateX(180*ofNoise(ofGetElapsedTimef()*.1));
    //    ofRotateZ(180*ofNoise(ofGetElapsedTimef()*.1 + 10));
    ofScale(2.5, 2.5, 2.5);
    
    ofEnableDepthTest();
    
    ofPushMatrix();
    // shapes and stuff matrix
    
    ofSetLineWidth(1);
    ofSetColor(230);

    ofPushMatrix();
        ofTranslate(0, topCone.getHeight() * .5);
        topCone.draw();
    ofPopMatrix();
    
//    ofPushMatrix();
//        ofTranslate(0, bottomCone.getHeight() * .5);
//        bottomCone.draw();
//    ofPopMatrix();

    
//    ofSetColor(255, 0, 0);
//    for(int i = 0; i < rays.size(); i++){
//        rays[i].draw();
//    }
    
    
    //plane.draw();
    
//    
//    ofPushMatrix();
//    
//    ofTranslate(plane.getCenter());
//    ofQuaternion q, r;
//    q.makeRotate(ofVec3f(0,0,1), plane.getNormal());
//    r.makeRotate(ofVec3f(0,1,0) * q, plane.getUp());
//    float angle, x, y, z;
//    (q * r).getRotate(angle, x, y, z);
//    ofRotate(angle, x, y, z);
//    ofScale(plane.getScale().x, plane.getScale().y, 1.0);
//    
//    ofSetColor(255,0,0);ofRectangle(0,0,400,400);
//    ofPopMatrix();
    
    
    
    
    ofDisableDepthTest();
    
    ofSetColor(0);
    ofSetLineWidth(2);
//    if(intersections.size() > 2){
//        for(int i = 0; i < intersections.size() - 1; i++){
//            ofDrawLine(intersections[i], intersections[i+1]);
//        }
//    }
    for(int i = 0; i < intersectionLines.size(); i++){
        intersectionLines[i].draw();
    }

    
    float normalAmount = sin(ofGetElapsedTimef() * 0.8) * 0.5 + 0.5;
    
    
    for (int z = 0; z < 20; z ++){
        
        intersectionLines.clear();
        
    // update position and orientation of the plane
    plane.setCenter(planeMouseOffset + ofVec3f(0, 100*ofNoise(ofGetElapsedTimef()*.4)-50 + z*1, 0));
    plane.setNormal(planeMouseOffset + ofVec3f(200 * ofNoise(ofGetElapsedTimef() * .4 + 10)-100,  normalAmount*cos(z+ofGetElapsedTimef()) * 100, normalAmount*sin(z) * 100 + 200 * ofNoise(ofGetElapsedTimef()*.4 + 20)-100 ));
    
    intersections.clear();
    // find all the intersections between the plane and the cones
    for(int i = 0; i < rays.size(); i++){
        ofVec3f intersect;
        if(plane.intersect(rays[i], intersect)){
            intersections.push_back(intersect);
        }
    }
    
    //now take these interesctions and clip them against the top and bottom of the cones
    intersectionLines.clear();
    ofPolyline polyline;
    intersectionLines.push_back(polyline);
    int whichIndex = 0;
    for(int i = 0; i < intersections.size(); i++){
        if(intersections[i].y > -CONE_HEIGHT && intersections[i].y < 0){//-CONE_HEIGHT){
            intersectionLines[whichIndex].addVertex(intersections[i]);
        }
        else if (intersectionLines[whichIndex].getVertices().size() > 0){
            ofPolyline polyline;
            intersectionLines.push_back(polyline);
            whichIndex++;
        }
        //        cur.setClosed(true);
    }
        
        for(int i = 0; i < intersectionLines.size(); i++){
            intersectionLines[i].draw();
        }
        
    
    }
    
    
    ofPopMatrix();
    
    ofPopMatrix();
    
    
    
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
    float dy = y - ofGetPreviousMouseY();
    planeMouseOffset.y += dy;
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
