#include "ofApp.h"

Point4D::Point4D(){
    x = 0;
    y = 0;
    z = 0;
    w = 0;
}
Point4D::Point4D(float xa, float ya, float za, float wa){
    x = xa;
    y = ya;
    z = za;
    w = wa;
}

void Point4D::rotate(ofMatrix4x4 m){
    ofVec4f point = ofVec4f(x, y, z, w);
    ofVec4f newPoint = point * m;
    x = newPoint.x;
    y = newPoint.y;
    z = newPoint.z;
    w = newPoint.w;
}

//void Point4D::rotate(float xRad, float yRad, float zRad, float wRad){
//    float r = sqrt( powf(x,2) + powf(y,2) + powf(z,2) + powf(w,2) );
//    float a1 = atan( 1/( (x)/(sqrt(powf(w,2)+powf(z,2)+powf(y,2))) ) );
//    float a2 = atan( 1/( (y)/(sqrt(powf(w,2)+powf(z,2))) ) );
//    float a3 = 2*atan( 1/( (z + sqrt(powf(w,2) + powf(z,2)))/w ) ); // special case
//    
//    
//}



void Polychron::loadVefFile(string file) {
    
    ifstream fin;
    fin.open( ofToDataPath(file).c_str() );
    
    unsigned int numVertices, numEdges, numFaces;
    numVertices = numEdges =  numFaces = 0;

    vertices.clear();
    edges.clear();
    faces.clear();
    _v.clear();
    _e.clear();
    _f.clear();
    
    fin >> numVertices;
    for(int i = 0; i < numVertices; i++){
        Point4D point;
        fin >> point.x >> point.y >> point.z >> point.w;
        vertices.push_back(point);
    }

    fin >> numEdges;
    for(int i = 0; i < numEdges; i++){
        unsigned int e1, e2;
        fin >> e1 >> e2;
        edges.push_back(e1);
        edges.push_back(e2);
    }

    
    // wait, faces is not always 4. sometimes it's 5 or 3.
    // need to change approach, need to fin and watch for line endings
    
//    fin >> numFaces;
//    for(int i = 0; i < numFaces; i++){
//        unsigned int f1, f2;
//        fin >> f1 >> f2;
//        faces.push_back(f1);
//        faces.push_back(f2);
//    }

    for(int i = 0; i < vertices.size(); i++)
        _v.push_back(vertices[i]);
    for(int i = 0; i < edges.size(); i++)
        _e.push_back(edges[i]);
    for(int i = 0; i < faces.size(); i++)
        _f.push_back(faces[i]);

    fin.close();
}

//void Polychron::rotate(float xRad, float yRad, float zRad, float wRad){
//    for(int i = 0; i < vertices.size(); i++){
//        vertices[i].rotate(xRad, yRad, zRad, wRad);
//    }
//}
void Polychron::rotate(ofMatrix4x4 m){
    for(int i = 0; i < vertices.size(); i++){
        vertices[i] = _v[i];
        vertices[i].rotate(m);
    }
}

void Polychron::drawWireframe(){
    
    float pct = 1.0;//0.5 + 0.5 * sin(ofGetElapsedTimef()); //ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 1, true);
    
    for(int i = 0; i < edges.size() * .5 * pct; i++){
        ofDrawLine(vertices[ edges[i*2+0] ].x, vertices[ edges[i*2+0] ].y, vertices[ edges[i*2+0] ].z,
                   vertices[ edges[i*2+1] ].x, vertices[ edges[i*2+1] ].y, vertices[ edges[i*2+1] ].z);
    }
}

void Polychron::log(){
    for(int i = 0; i < vertices.size(); i++)
        printf("(%.1f, %.1f, %.1f, %.1f)\n", vertices[i].x, vertices[i].y, vertices[i].z, vertices[i].w);
    for(int i = 0; i < edges.size()*.5; i++)
        printf("(%d, %d)\n", edges[i*2], edges[i*2+1]);
//    for(int i = 0; i < faces.size()*.5; i++)
//        printf("(%d, %d)\n", faces[i*2], faces[i*2+1]);
    
}


//--------------------------------------------------------------
void ofApp::setup(){
    polychron.loadVefFile("16cell.ascii.txt");
    a1 = a2 = a3 = 0;
}

float da2 = 0;
float da3 = 0;

//--------------------------------------------------------------
void ofApp::update(){
    
    a2 += da2;
    a3 += da3;
    
//    ofMatrix4x4 rotation = ofMatrix4x4(<#float a00#>, <#float a01#>, <#float a02#>, <#float a03#>,
//                                       <#float a10#>, <#float a11#>, <#float a12#>, <#float a13#>,
//                                       <#float a20#>, <#float a21#>, <#float a22#>, <#float a23#>,
//                                       <#float a30#>, <#float a31#>, <#float a32#>, <#float a33#>);
    
//    ofMatrix4x4 rotation = ofMatrix4x4(cosf(a1), -sinf(a1),        0,         0,
//                                       sinf(a1),  cosf(a1),        0,         0,
//                                       0,         0,        cosf(a2), -sinf(a2),
//                                       0,         0,        sinf(a2),  cosf(a2) );

    ofMatrix4x4 rotateA1 = ofMatrix4x4(cosf(a1), 0,        0, -sinf(a1),
                                       0,        1,        0,         0,
                                       0,        0,        1,         0,
                                       sinf(a1), 0,        0,   cosf(a1) );
    
    ofMatrix4x4 rotateA2 = ofMatrix4x4(1,         0,        0,         0,
                                       0,  cosf(a2),        0, -sinf(a2),
                                       0,         0,        1,         0,
                                       0,  sinf(a2),        0,  cosf(a2) );

    ofMatrix4x4 rotateA3 = ofMatrix4x4(1,         0,        0,         0,
                                       0,         1,        0,         0,
                                       0,         0, cosf(a3), -sinf(a3),
                                       0,         0, sinf(a3),  cosf(a3) );
    
    
    
    ofMatrix4x4 rotation = ofMatrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
//    rotation *= rotateA1;
    rotation *= rotateA2;
    rotation *= rotateA3;
    polychron.rotate(rotation);
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //cam.lookAt(ofPoint(0,0,0));
    //cam.setPosition(200 + 80 * sin(ofGetElapsedTimef()), 0, 200);
    
    ofClear(0);
    ofSetColor(255);
    ofPushMatrix();
//    ofTranslate(ofGetWidth()*.5, ofGetHeight()*.5);
    cam.begin();
    ofScale(100, 100, 100);
    polychron.drawWireframe();
    cam.end();
//    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_RIGHT){
        da3 = 0.01;
    }
    else if(key == OF_KEY_LEFT){
        da3 = -0.01;
    }
    else if(key == OF_KEY_UP){
        da2 = 0.01;
    }
    else if(key == OF_KEY_DOWN){
        da2 = -0.01;
    }
    else
        da3 = 0;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    da3 = 0;
    da2 = 0;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
//    float dx = x - adder
//    float dy = y - ofGetPreviousMouseY();
//    a1 += dx * .1;
//    a2 += dy * .1;
//    a3 += dx * .1;

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

    cout << dragInfo.files[0] << endl;
    polychron.loadVefFile(dragInfo.files[0]);

}
