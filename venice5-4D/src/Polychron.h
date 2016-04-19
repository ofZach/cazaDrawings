#pragma once

#include "ofMain.h"
#include "Polychron.h"

class Point4D : public ofBaseApp{
public:
    float x, y, z, w;
    Point4D();
    Point4D(float x, float y, float z, float w);
    
    void rotate(ofMatrix4x4 m);
};

class Polychron : public ofBaseApp {
    
public:
    Polychron();
    void loadVefFile(string file);
    void drawWireframe();
    
    // proper rotaiton (includes all 4D)
    void rotate(ofMatrix4x4 m); // cumulative.  all 4 cols/rows are used for rotation, not 3 with 1 translation like traditional 3D graphics
    
    // only 4D rotation
    void rotate4DOnly(float dwx, float dwy, float dwz);  // non cumulative
    
    void log();  // printf vertices, edges, faces
    
private:
    float wx, wy, wz;  // RADIANS, angle of rotations (each through the 4th dimension)
    vector<Point4D> vertices;
    vector<unsigned int> edges; // indices in vertices array
    vector<unsigned int> faces;  // indices in vertices array
    unsigned int verticesPerFace; // TODO
    
    // definitely private
    vector<Point4D> _v;
    vector<unsigned int> _e;
    vector<unsigned int> _f;
};
