#include "ofApp.h"

//--------------------------------------------------------------
//       SVG MESH CLASS
//--------------------------------------------------------------

void SVGMesh::loadSVG(string path){
    
    // empty out last object
    vertices.clear();
    lines.clear();

    ofxSVG svg;
    svg.load(path);
    
    // build array of unique vertices
    for (int i = 0; i < svg.getNumPath(); i++){
        ofPath p = svg.getPathAt(i);
        p.setPolyWindingMode(OF_POLY_WINDING_ODD);
        vector<ofPolyline>& svgLines = const_cast<vector<ofPolyline>&>(p.getOutline());
        for(int j=0;j<(int)svgLines.size();j++){
            vector<ofPoint> thesePoints = svgLines[j].getVertices();
            for(int k = 0; k < thesePoints.size(); k++){
                addVertex(thesePoints[k]);
            }
        }
    }
    for(int i = 0; i < vertices.size(); i++){
        ofPoint p = vertices[i];
        homeVertices.push_back(p);
        inertia.push_back( ofRandom(0.3, 1.0) );
    }
//    printf("unique vertices :%d", (int)vertices.size());
    
    // build array of lines connecting to these vertices
    for (int i = 0; i < svg.getNumPath(); i++){
        ofPath p = svg.getPathAt(i);
        vector<ofPolyline>& svgLines = const_cast<vector<ofPolyline>&>(p.getOutline());
        for(int j=0;j<(int)svgLines.size();j++){
            vector<ofPoint> thesePoints = svgLines[j].getVertices();
            for(int k = 0; k < thesePoints.size()-1; k++){
                unsigned int index1, index2;
                if(indexOfVertexMatchingPoint(&index1, thesePoints[k], 0.5) &&
                   indexOfVertexMatchingPoint(&index2, thesePoints[k+1], 0.5)){
                    lines.push_back(index1);
                    lines.push_back(index2);
                }
            }
        }
    }
//    printf("line indices count (should be even):%d", (int)lines.size());
}
void SVGMesh::addVertex(ofPoint point){
    bool match = false;
    int i = 0;
    while(i < vertices.size() && !match){
        match = pointsAreEqual(vertices[i], point, .5);
        i++;
    }
    if(!match)
        vertices.push_back(point);
}

bool SVGMesh::indexOfVertexMatchingPoint(unsigned int *index, ofPoint point, float radius){
    bool match = false;
    int i = 0;
    while(i < vertices.size() && !match){
        match = pointsAreEqual(vertices[i], point, .5);
        i++;
    }
    if(match){
        *index = i-1;
        return true;
    }
    return false;
}

bool SVGMesh::pointsAreEqual(ofPoint p1, ofPoint p2, float radius){
    // quick manhattan distance is good enough for now, avoiding distance formula
    if( fabs(p1.x - p2.x) < radius && fabs(p1.y - p2.y) < radius)
        return true;
    return false;
}

void SVGMesh::draw(){
    int halfLineCount = lines.size() * .5;
    for(int i = 0; i < halfLineCount; i++){
        ofDrawLine(vertices[ lines[i*2+0] ], vertices[ lines[i*2+1] ]);
    }
}

void SVGMesh::update(){
    static float SCALER = .2;
    for(int i = 0; i < vertices.size(); i++){
        ofVec3f diff = homeVertices[i] - vertices[i];
        vertices[i] += diff * SCALER * inertia[i];
        if(pointsAreEqual(homeVertices[i], vertices[i], 0.2)){
            vertices[i] = homeVertices[i];
        }
    }
}

void SVGMesh::pushVertices(ofVec3f force){
    for(int i = 0; i < vertices.size(); i++){
        vertices[i] += force;// * magnitude;
    }
}

//--------------------------------------------------------------
//       OF APP CLASS
//--------------------------------------------------------------
void ofApp::setup(){
    
    obj.loadSVG("four.svg");
    
    ofBackground(255);
    ofSetColor(0);
    
    svg.load("four.svg");
    for (int i = 0; i < svg.getNumPath(); i++){
        ofPath p = svg.getPathAt(i);
        // svg defaults to non zero winding which doesn't look so good as contours
        p.setPolyWindingMode(OF_POLY_WINDING_ODD);
        vector<ofPolyline>& lines = const_cast<vector<ofPolyline>&>(p.getOutline());
        for(int j=0;j<(int)lines.size();j++){
            outlines.push_back(lines[j].getResampledBySpacing(1));
        }
    }
    
    stepVel = 0.01;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    float xDiff = fabs(ofGetMouseX() - ofGetPreviousMouseX());
    float yDiff = fabs(ofGetMouseY() - ofGetPreviousMouseY());
    float v = sqrt(powf(xDiff, 2) + powf(yDiff, 2));
    float temp = 1.0 - v*.01;
    if(temp < 0)
        temp = 0;

    if(step > temp){
        step = temp;
        stepVel = .0001;
    }
    stepVel *= 1.3;
    
    step += stepVel;
    if(step > 1)
        step = 1;
    
    temp+=0.05;
    if(temp > 1) temp = 1;
    
    obj.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
    ofPushMatrix();
//    ofTranslate(ofGetWidth()*.5, ofGetHeight()*.5);
    ofTranslate(ofGetMouseX(), ofGetMouseY());
    //    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    //    ofRotate(mouseX);
    float scale = ofGetHeight() * .005;
    ofScale(scale, scale, scale);
    ofTranslate(-75, -75);
    ofNoFill();

    
    obj.draw();
    
    
    ofPopMatrix();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    int px = ofGetPreviousMouseX();
    int py = ofGetPreviousMouseY();
    obj.pushVertices(ofVec3f((px - x)*.3, (py - y)*.3, 0));

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
