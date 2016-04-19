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

Polychron::Polychron(){
    wx = wy = wz = 0;
}

void Polychron::loadVefFile(string file) {
    
    wx = wy = wz = 0;
    vertices.clear();
    edges.clear();
    faces.clear();
    _v.clear();
    _e.clear();
    _f.clear();

    unsigned int numVertices, numEdges, numFaces;
    numVertices = numEdges =  numFaces = 0;
    
    ifstream fin;
    fin.open( ofToDataPath(file).c_str() );
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

void Polychron::rotate(ofMatrix4x4 m){
    for(int i = 0; i < vertices.size(); i++){
        vertices[i] = _v[i];
        vertices[i].rotate(m);
    }
}

void Polychron::rotate4DOnly(float dwx, float dwy, float dwz){
    wx += dwx;
    wy += dwy;
    wz += dwz;
    
    ofMatrix4x4 rotateA1 = ofMatrix4x4(cosf(wx), 0,        0, -sinf(wx),
                                       0,        1,        0,         0,
                                       0,        0,        1,         0,
                                       sinf(wx), 0,        0,   cosf(wx) );
    ofMatrix4x4 rotateA2 = ofMatrix4x4(1,         0,        0,         0,
                                       0,  cosf(wy),        0, -sinf(wy),
                                       0,         0,        1,         0,
                                       0,  sinf(wy),        0,  cosf(wy) );
    ofMatrix4x4 rotateA3 = ofMatrix4x4(1,         0,        0,         0,
                                       0,         1,        0,         0,
                                       0,         0, cosf(wz), -sinf(wz),
                                       0,         0, sinf(wz),  cosf(wz) );
    ofMatrix4x4 rotation = ofMatrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    rotation *= rotateA1;
    rotation *= rotateA2;
    rotation *= rotateA3;
    rotate(rotation);
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
