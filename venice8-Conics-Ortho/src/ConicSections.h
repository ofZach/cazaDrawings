#pragma once

#include "ofxRay.h"

class ConicSections : public ofBaseApp{
    
public:
    ConicSections();
    ConicSections(float aConeHeight, float aConeRadius);
    
    void drawCones();
    void drawIntersectionLines(vector<ofxRay::Plane> planes);
    void drawIntersectionFills(vector<ofxRay::Plane> planes);

    // hides cones and computations associated with them
    bool topConeHidden;
    bool bottomConeHidden;
    
    // add planes here for intersections
    vector <ofxRay::Plane> planes;
    
//private:
    // cones
    ofConePrimitive topCone;
    ofConePrimitive bottomCone;
    vector<ofxRay::Ray> topConeRays;
    vector<ofxRay::Ray> bottomConeRays;
    
    float coneHeight;
    float coneRadius;
    
private:
    // intersections
    vector<ofPolyline>topIntersectionLines, bottomIntersectionLines;
    bool insideBounds(float yValue); // based on top/bottom cones hidden
    
};
