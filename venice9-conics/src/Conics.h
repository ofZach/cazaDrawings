#pragma once

#include "ofMain.h"

#define RESOLUTION 50

class Conics : public ofBaseApp{
public:
    
    Conics();
    
    // the parent node - use to move around
    ofNode cone; // lies at the apex
    
    // the parts of the cone
    ofNode apex;  // the tip of the cone
    ofNode base;  // center of the base plane
    float radius; // radius of the base plane
    ofVec3f focus; // the direction the cone faces
    
    ofNode basePoints[RESOLUTION];
    
    // functions
    void draw();
    void drawIntersectionsWithPlane(ofVec3f planePt, ofVec3f planeNormal);
    
    ofVec3f crossProduct(ofVec3f A1, ofVec3f A2);
    float dotProduct(ofVec3f A1, ofVec3f A2);
    bool linePlaneIntersect(ofVec3f *intersection, ofVec3f line0, ofVec3f line1, ofVec3f planeP, ofVec3f planeN);

};