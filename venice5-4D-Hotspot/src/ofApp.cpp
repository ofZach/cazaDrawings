#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    for(int i = 0; i < NUM_POLY; i++){
        polychron[i].loadVefFile("120cell.ascii.txt");
        highlighted[i].clear();
    }
    hotSpot = ofPoint(ofGetWidth()*.5, ofGetHeight()*.5);
    hotSpotRadius = 80;
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
        
        // decrement the edge energy
        for(int e = 0 ; e < polychron[i].edgeEnergy.size(); e++)
            polychron[i].edgeEnergy[e] *= 0.98;
        for(int e = 0 ; e < polychron[i].vertexEnergy.size(); e++)
            polychron[i].vertexEnergy[e] *= 0.98;
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

bool ofApp::pointInHotspot(ofPoint point){
    return ( sqrt( powf(point.x - hotSpot.x, 2) + powf(point.y - hotSpot.y, 2)) < hotSpotRadius );
}

//--------------------------------------------------------------
void ofApp::draw(){

    
    
    
    ofClear(0);

    ofSetColor(255);
    ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
    
    cam.lookAt(ofPoint(0,0,0));
    cam.setPosition(25 * sin(ofGetElapsedTimef()*.2), 25 * cosf(ofGetElapsedTimef()*.2), 20);
    
//    ofTranslate(ofGetWidth()*.5, ofGetHeight()*.5);
    
    
//    ofSetColor(255, 50);
//    ofNoFill();
//    ofDrawCircle(hotSpot.x, hotSpot.y, hotSpotRadius);
//    ofDrawLine(ofGetWidth()*.5, 0, ofGetWidth()*.5, ofGetHeight());
//    ofFill();
//    ofSetColor(255);
    
    ofMatrix4x4 polyMatrix;
    
    cam.begin();

    ofPushMatrix();
//    ofScale(100, 100, 100);
    for(int i = 0; i < NUM_POLY; i++){
        ofPushMatrix();
        
        polyMatrix = ofMatrix4x4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
        polyMatrix.scale(100, 100, 100);
        if(i == 1){
            polyMatrix.translate(i*0.1, i*0, 0);
            polyMatrix.rotate(45, 1, 0, 0);
            polyMatrix.scale(1.5, 1.5, 1.5);
        }

        ofSetColor(255, 50);
        ofMultMatrix(polyMatrix);
        polychron[i].drawWireframe();
        
        
        // CALCULATE the highlighted vertices
        highlighted[i].clear();
        for(int v = 0; v < polychron[i].getNumVertices(); v++){
            Point4D vertex = polychron[i].vertices[v];
            ofVec3f screenLocation = worldToScreen( ofVec3f(vertex.x, vertex.y, vertex.z), polyMatrix );
            if(pointInHotspot(screenLocation)){
                //                if(screenLocation.x < ofGetWidth()*.5){
                highlighted[i].push_back(v);
                // vertex energy
                polychron[i].vertexEnergy[v] += 0.05;
                if(polychron[i].vertexEnergy[ v ] > 1)
                    polychron[i].vertexEnergy[ v ] = 1;
                // edge energy
                vector<unsigned int> adjEdg = polychron[i].allEdgesAdjacentTo(v);
                for(int q = 0; q < adjEdg.size(); q++){
                    polychron[i].edgeEnergy[ adjEdg[q] ] += .05;
                    if(polychron[i].edgeEnergy[ adjEdg[q] ] > 1)
                        polychron[i].edgeEnergy[ adjEdg[q] ] = 1;
                }
            }
        }
  
        
        for(int e = 0; e < polychron[i].edges.size() * .5; e++){
//            ofSetColor(255, 255* polychron[i].edgeEnergy[e]);
//            ofDrawLine(polychron[i].vertices[ polychron[i].edges[e*2+0] ].x,
//                       polychron[i].vertices[ polychron[i].edges[e*2+0] ].y,
//                       polychron[i].vertices[ polychron[i].edges[e*2+0] ].z,
//                       polychron[i].vertices[ polychron[i].edges[e*2+1] ].x,
//                       polychron[i].vertices[ polychron[i].edges[e*2+1] ].y,
//                       polychron[i].vertices[ polychron[i].edges[e*2+1] ].z);

            ofMesh myMesh;
            myMesh.setMode(OF_PRIMITIVE_LINES);
            myMesh.addVertex( polychron[i].vertices[ polychron[i].edges[e*2+0] ].threeD() );
            myMesh.addColor(ofColor( 255* polychron[i].vertexEnergy[ polychron[i].edges[e*2+0] ] ));
            myMesh.addVertex( polychron[i].vertices[ polychron[i].edges[e*2+1] ].threeD() );
            myMesh.addColor(ofColor( 255* polychron[i].vertexEnergy[ polychron[i].edges[e*2+1] ] ));
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            myMesh.draw();

        }
        // DRAW the highlighted vertices
//        ofSetColor(255, 50);
//        for(int h = 0; h < highlighted[i].size(); h++){
//            ofDrawSphere(polychron[i].vertices[highlighted[i][h]].x,
//                         polychron[i].vertices[highlighted[i][h]].y,
//                         polychron[i].vertices[highlighted[i][h]].z, .06);
//        }
        ofPopMatrix();
    }
    ofPopMatrix();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    static float ROT_SPEED = 0.001;
    
    if(key == OF_KEY_RIGHT)
        da3 = ROT_SPEED;
    else if(key == OF_KEY_LEFT)
        da3 = -ROT_SPEED;
    if(key == OF_KEY_UP)
        da2 = ROT_SPEED;
    else if(key == OF_KEY_DOWN)
        da2 = -ROT_SPEED;
    if(key == '[')
        da1 = ROT_SPEED;
    else if(key == ']')
        da1 = -ROT_SPEED;
    
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
