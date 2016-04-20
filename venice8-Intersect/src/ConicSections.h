#pragma once

#include "ofxRay.h"

#define CONE_RESOLUTION 1000
#define CONE_RADIUS 50
#define CONE_HEIGHT 100

class ConicSections : public ofBaseApp{
    
public:
    ConicSections();
    
    void drawCones();
    void drawIntersectionLines(vector<ofxRay::Plane> planes);
    void drawIntersectionFills(vector<ofxRay::Plane> planes);

    // hides cones and computations associated with them
    bool topConeHidden;
    bool bottomConeHidden;
    
    // add planes here for intersections
    vector <ofxRay::Plane> planes;
    
private:
    // cones
    ofConePrimitive topCone;
    ofConePrimitive bottomCone;
    vector<ofxRay::Ray> topConeRays;
    vector<ofxRay::Ray> bottomConeRays;
    ofxRay::Plane topConePlane;
    ofxRay::Plane bottomConePlane;
    
private:
    // intersections
    vector<ofPolyline>topIntersectionLines, bottomIntersectionLines;
    bool insideBounds(float yValue); // based on top/bottom cones hidden
    
};
