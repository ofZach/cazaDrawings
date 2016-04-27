#include "ofApp.h"


// mouth: 48,60 (48,54)
// head: 0,67 (3,13)
// eyeL: 36,41 (36,39)
// eyeR: 42,47 (42,45)
// nose: 29,35 (31,35)

// mouth: 51-top-middle, 57-bottom middle

//--------------------------------------------------------------
void ofApp::setup(){
    PL.setup();

    for(int i = 0; i < NUM_POLY; i++){
        polychron[i].loadVefFile("8cell.ascii.txt");
        highlighted[i].clear();
    }
    hotSpots.push_back( ofPoint(ofGetWidth()*.3, ofGetHeight()*.2) );
    hotSpots.push_back( ofPoint(ofGetWidth()*.7, ofGetHeight()*.2) );
    hotSpots.push_back( ofPoint(ofGetWidth()*.5, ofGetHeight()*.75) );
    hotSpotRadius = 60;
    
    myShader.load("gradient");

    faceOriginOffset = ofPoint(-380, -260);
    
    for(int i = 0; i < NUM_POLY; i++){
        rotations[i].x = ofRandom(.01, 0.3);
        rotations[i].y = ofRandom(.01, 0.3);
        rotations[i].z = ofRandom(.01, 0.3);
    }
    // build matrices
    faceMatrix = ofMatrix4x4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
    faceMatrix.translate(faceOriginOffset.x, faceOriginOffset.y, 0);
    faceMatrix.rotate(180, 0, 0, 1);
    
    for(int i = 0 ;i < NUM_POLY; i++){
        polyMatrix[i] = ofMatrix4x4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
        polyMatrix[i].scale(100, 100, 100);
        // add some rotations and scales between polychrons and increasingly scale them up
        polyMatrix[i].translate(i*0.1, i*0, 0);
        polyMatrix[i].rotate(i*45, 1, 0, 0);
        polyMatrix[i].rotate((i%2)*90, 0, 1, 0);
        polyMatrix[i].rotate( (floor(i/2)*45), 0, 0, 1);
        polyMatrix[i].scale(1+i*0.5, 1+i*0.5, 1+i*0.5);
    }

}

//--------------------------------------------------------------
void ofApp::update(){
    PL.update();
    
//    hotSpots[0] = PL.ptData[PL.frame][51] - faceOriginOffset;
//    hotSpots[1] = PL.ptData[PL.frame][36] - faceOriginOffset;
//    hotSpots[2] = PL.ptData[PL.frame][42] - faceOriginOffset;
    
    hotSpots[0] = worldToScreen( PL.ptData[PL.frame][51], faceMatrix );
    hotSpots[1] = worldToScreen( PL.ptData[PL.frame][36], faceMatrix );
    hotSpots[2] = worldToScreen( PL.ptData[PL.frame][42], faceMatrix );

    
//    printf("%f, %f %f\n", PL.ptData[PL.frame][51].x,
//           PL.ptData[PL.frame][51].y,
//           PL.ptData[PL.frame][51].z);
    
    
    if (ofGetFrameNum() % 60 == 0){
        myShader.load("gradient");
    }
    
    float SCALE = .002;
    for(int i = 0; i < NUM_POLY; i++){
        polychron[i].rotate4DOnly(SCALE * sinf(ofGetElapsedTimef() * rotations[i].x),
                                  SCALE * sinf(ofGetElapsedTimef() * rotations[i].y),
                                  SCALE * sinf(ofGetElapsedTimef() * rotations[i].z) );
    }
    
    for(int i = 0; i < NUM_POLY; i++) {
        // CALCULATE the highlighted vertices
        highlighted[i].clear();
        for(int v = 0; v < polychron[i].getNumVertices(); v++){
            Point4D vertex = polychron[i].vertices[v];
            ofVec3f screenLocation = worldToScreen( ofVec3f(vertex.x, vertex.y, vertex.z), polyMatrix[i] );
            if(pointInHotspot(hotSpots[0], screenLocation) ||
               pointInHotspot(hotSpots[1], screenLocation) ||
               pointInHotspot(hotSpots[2], screenLocation)){
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

bool ofApp::pointInHotspot(ofPoint hotSpot, ofPoint point){
    return ( sqrt( powf(point.x - hotSpot.x, 2) + powf(point.y - hotSpot.y, 2)) < hotSpotRadius );
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofClear(0);

    ofSetColor(255);
    ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
    ofSetColor(255, 50);
    ofNoFill();
    for(int i = 0 ;i < 3; i++){
//        ofDrawCircle(hotSpots[i].x, hotSpots[i].y, hotSpotRadius);
    }
    ofFill();

    
    cam.begin();

//    // draw face
//    ofSetColor(255, 64);
//    ofPushMatrix();
//    ofMultMatrix(faceMatrix);
//    PL.draw();
//    ofPopMatrix();
    
   
    
//    float camRadius = 100;
//    float camSpeed = .1;
//    cam.lookAt(ofPoint(0,0,0));
//    cam.setPosition(camRadius * sin(ofGetElapsedTimef()*camSpeed), camRadius * cosf(ofGetElapsedTimef()*camSpeed), 100);
    

    ofSetColor(255);

    ofPushMatrix();
    
    for(int i = 0; i < NUM_POLY; i++){
        ofPushMatrix();
        
        myShader.begin();
        myShader.setUniform2f("ptToFadeFrom1", ofVec2f(hotSpots[0].x, ofGetHeight() - hotSpots[0].y));
        myShader.setUniform2f("ptToFadeFrom2", ofVec2f(hotSpots[1].x, ofGetHeight() - hotSpots[1].y));
        myShader.setUniform2f("ptToFadeFrom3", ofVec2f(hotSpots[2].x, ofGetHeight() - hotSpots[2].y));
        ofMultMatrix(polyMatrix[i]);
        
        ofSetColor(255, 50);
        polychron[i].drawWireframe();
        myShader.end();
        
        for(int e = 0; e < polychron[i].edges.size() * .5; e++){
            ofMesh myMesh;
            myMesh.setMode(OF_PRIMITIVE_LINES);
            myMesh.addVertex( polychron[i].vertices[ polychron[i].edges[e*2+0] ].threeD() );
            myMesh.addColor(ofColor( 255* polychron[i].vertexEnergy[ polychron[i].edges[e*2+0] ] ));
            myMesh.addVertex( polychron[i].vertices[ polychron[i].edges[e*2+1] ].threeD() );
            myMesh.addColor(ofColor( 255* polychron[i].vertexEnergy[ polychron[i].edges[e*2+1] ] ));
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            myMesh.draw();
        }
        ofPopMatrix();
    }
    
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
