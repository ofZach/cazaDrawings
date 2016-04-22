#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    for(int i = 0; i < NUM_POLY; i++){
        polychron[i].loadVefFile("8cell.ascii.txt");
        highlighted[i].clear();
    }
    hotSpots.push_back( ofPoint(ofGetWidth()*.3, ofGetHeight()*.2) );
    hotSpots.push_back( ofPoint(ofGetWidth()*.7, ofGetHeight()*.2) );
    hotSpots.push_back( ofPoint(ofGetWidth()*.5, ofGetHeight()*.75) );
    hotSpotRadius = 60;

    myShader.load("gradient");
}

float da1 = 0;
float da2 = 0;
float da3 = 0;

float ax[NUM_POLY], ay[NUM_POLY], az[NUM_POLY];

//--------------------------------------------------------------
void ofApp::update(){
    
    if (ofGetFrameNum() % 60 == 0){
        myShader.load("gradient");
    }
    
    float SCALE = .002;
    
    da1 = SCALE * sinf(ofGetElapsedTimef()*.022);
    da2 = SCALE * cosf(ofGetElapsedTimef()*.036);
    da3 = SCALE * (-sinf(ofGetElapsedTimef()*.0777));

    ax[0] = SCALE * sinf(ofGetElapsedTimef()*.022);
    ax[1] = SCALE * cosf(ofGetElapsedTimef()*.032);
    ax[2] = SCALE * -sinf(ofGetElapsedTimef()*.92);
    ax[3] = SCALE * -cosf(ofGetElapsedTimef()*.046);
    ax[4] = SCALE * sinf(ofGetElapsedTimef()*.027);
    ax[5] = SCALE * cosf(ofGetElapsedTimef()*.032);
//    ax[6] = SCALE * -sinf(ofGetElapsedTimef()*.072);
//    ax[7] = SCALE * -cosf(ofGetElapsedTimef()*.02);
    
    ay[0] = SCALE * sinf(ofGetElapsedTimef()*.055);
    ay[1] = SCALE * cosf(ofGetElapsedTimef()*.039);
    ay[2] = SCALE * -sinf(ofGetElapsedTimef()*.33);
    ay[3] = SCALE * -cosf(ofGetElapsedTimef()*.055);
    ay[4] = SCALE * sinf(ofGetElapsedTimef()*.073);
    ay[5] = SCALE * cosf(ofGetElapsedTimef()*.094);
//    ay[6] = SCALE * -sinf(ofGetElapsedTimef()*.017);
//    ay[7] = SCALE * -cosf(ofGetElapsedTimef()*.039);
    
    az[0] = SCALE * sinf(ofGetElapsedTimef()*.065);
    az[1] = SCALE * cosf(ofGetElapsedTimef()*.035);
    az[2] = SCALE * -sinf(ofGetElapsedTimef()*.785);
    az[3] = SCALE * -cosf(ofGetElapsedTimef()*.0872);
    az[4] = SCALE * sinf(ofGetElapsedTimef()*.081);
    az[5] = SCALE * cosf(ofGetElapsedTimef()*.093);
//    az[6] = SCALE * -sinf(ofGetElapsedTimef()*.028);
//    az[7] = SCALE * -cosf(ofGetElapsedTimef()*.058);

//    ax[8] = SCALE * sinf(ofGetElapsedTimef()*.062);
//    ax[9] = SCALE * cosf(ofGetElapsedTimef()*.042);
//    ax[10] = SCALE * -sinf(ofGetElapsedTimef()*.072);
//    ax[11] = SCALE * -cosf(ofGetElapsedTimef()*.066);
//    ax[12] = SCALE * sinf(ofGetElapsedTimef()*.047);
//    ax[13] = SCALE * cosf(ofGetElapsedTimef()*.082);
//    ax[14] = SCALE * -sinf(ofGetElapsedTimef()*.022);
//    ax[15] = SCALE * -cosf(ofGetElapsedTimef()*.062);
//    
//    ay[8] = SCALE * sinf(ofGetElapsedTimef()*.055);
//    ay[9] = SCALE * cosf(ofGetElapsedTimef()*.089);
//    ay[10] = SCALE * -sinf(ofGetElapsedTimef()*.023);
//    ay[11] = SCALE * -cosf(ofGetElapsedTimef()*.045);
//    ay[12] = SCALE * sinf(ofGetElapsedTimef()*.053);
//    ay[13] = SCALE * cosf(ofGetElapsedTimef()*.074);
//    ay[14] = SCALE * -sinf(ofGetElapsedTimef()*.027);
//    ay[15] = SCALE * -cosf(ofGetElapsedTimef()*.069);
//    
//    az[8] = SCALE * sinf(ofGetElapsedTimef()*.045);
//    az[9] = SCALE * cosf(ofGetElapsedTimef()*.065);
//    az[10] = SCALE * -sinf(ofGetElapsedTimef()*.0385);
//    az[11] = SCALE * -cosf(ofGetElapsedTimef()*.0272);
//    az[12] = SCALE * sinf(ofGetElapsedTimef()*.071);
//    az[13] = SCALE * cosf(ofGetElapsedTimef()*.063);
//    az[14] = SCALE * -sinf(ofGetElapsedTimef()*.048);
//    az[15] = SCALE * -cosf(ofGetElapsedTimef()*.038);
    
    // KEYBOARD ROTATIONS
//    float less = 0.7;
//    float angle1 = da1;
//    float angle2 = da2;
//    float angle3 = da3;
    for(int i = 0; i < NUM_POLY; i++){
//        polychron[i].rotate4DOnly(angle1, angle2, angle3);
//        angle1 *= less;
//        angle2 *= less;
//        angle3 *= less;

        polychron[i].rotate4DOnly(ax[i], ay[i], az[i]);
        
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

bool ofApp::pointInHotspot(ofPoint hotSpot, ofPoint point){
    return ( sqrt( powf(point.x - hotSpot.x, 2) + powf(point.y - hotSpot.y, 2)) < hotSpotRadius );
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(0);

    ofSetColor(255);
    ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
    
    float camRadius = 100;
    float camSpeed = .1;
    cam.lookAt(ofPoint(0,0,0));
    cam.setPosition(camRadius * sin(ofGetElapsedTimef()*camSpeed), camRadius * cosf(ofGetElapsedTimef()*camSpeed), 100);
    
    
    
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
    
//    myShader.setUniform2f("ptToFadeFrom", ofVec2f(ofGetWidth()/2 + ofRandom(-mouseY,mouseY), ofGetHeight()/2 + ofRandom(-mouseY,mouseY)));


    for(int i = 0; i < NUM_POLY; i++){
        ofPushMatrix();
        
        polyMatrix = ofMatrix4x4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
        polyMatrix.scale(100, 100, 100);
        polyMatrix.translate(i*0.1, i*0, 0);
        polyMatrix.rotate(i*45, 1, 0, 0);
        polyMatrix.rotate((i%2)*90, 0, 1, 0);
        polyMatrix.rotate( (floor(i/2)*45), 0, 0, 1);
        polyMatrix.scale(1+i*0.5, 1+i*0.5, 1+i*0.5);

        myShader.begin();
        myShader.setUniform2f("ptToFadeFrom1", ofVec2f(hotSpots[0].x, ofGetHeight() - hotSpots[0].y));
        myShader.setUniform2f("ptToFadeFrom2", ofVec2f(hotSpots[1].x, ofGetHeight() - hotSpots[1].y));
        myShader.setUniform2f("ptToFadeFrom3", ofVec2f(hotSpots[2].x, ofGetHeight() - hotSpots[2].y));
        ofSetColor(255, 50);
        ofMultMatrix(polyMatrix);
        polychron[i].drawWireframe();
        myShader.end();
        
        
        // CALCULATE the highlighted vertices
        highlighted[i].clear();
        for(int v = 0; v < polychron[i].getNumVertices(); v++){
            Point4D vertex = polychron[i].vertices[v];
            ofVec3f screenLocation = worldToScreen( ofVec3f(vertex.x, vertex.y, vertex.z), polyMatrix );
            if(pointInHotspot(hotSpots[0], screenLocation) ||
               pointInHotspot(hotSpots[1], screenLocation) ||
               pointInHotspot(hotSpots[2], screenLocation)){
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
//    if(key == '[' || key == ']')
//        da1 = 0;
//    if(key == OF_KEY_UP || key == OF_KEY_DOWN)
//        da2 = 0;
//    if(key == OF_KEY_RIGHT || key == OF_KEY_LEFT)
//        da3 = 0;
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
