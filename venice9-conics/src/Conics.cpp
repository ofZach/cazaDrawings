#include "Conics.h"

Conics::Conics(){
    radius = 50;
    focus = ofVec3f(0, 0, 0);
    apex.setPosition(0,0,100);
    apex.lookAt( focus );
    cone.setPosition(0,0,100);
    cone.lookAt( focus );

    base.setPosition(0, 0, 0);
    base.setParent( apex );
    
    for(int i = 0; i < RESOLUTION; i++){
        float angle = ofMap(i, 0, RESOLUTION, 0, TWO_PI);
        basePoints[i].setPosition( radius * ofVec3f( cos(angle), sin(angle), 0 ) );
        basePoints[i].setParent( apex );
    }
}

void Conics::drawIntersectionsWithPlane(ofVec3f planePt, ofVec3f planeNormal){
    ofVec3f intersect;
    ofVec3f ap = apex.getPosition() * cone.getLocalTransformMatrix();
    for(int i = 0; i < RESOLUTION; i++){
        ofVec3f bp = basePoints[i].getPosition() * cone.getLocalTransformMatrix();
        if(linePlaneIntersect(&intersect, ap, bp, planePt, planeNormal)){
            ofDrawBox(intersect, 1);
        }
    }
}

void Conics::draw(){
    cone.transformGL();
    for(int i = 0; i < RESOLUTION; i++)
        ofDrawLine(apex.getPosition(), basePoints[i].getPosition());
    cone.restoreTransformGL();
}


float Conics::dotProduct(ofVec3f a, ofVec3f b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

ofVec3f Conics::crossProduct(ofVec3f a, ofVec3f b){
    float x = a[1] * b[2] - a[2] * b[1];
    float y = a[2] * b[0] - a[0] * b[2];
    float z = a[0] * b[1] - a[1] * b[0];
    return(ofVec3f(x, y, z));
}

bool Conics::linePlaneIntersect(ofVec3f *intersection, ofVec3f linePt1, ofVec3f linePt2, ofVec3f planePt, ofVec3f planeN){
    // line is defined by 2 points on a line
    // plane is defined by planeP point in the plane with normal planeN
    
    ofVec3f l = (linePt2 - linePt1);
    
    float numerator = dotProduct(planeN, (planePt - linePt1) );
    float denominator = dotProduct(planeN, l);
    if(denominator != 0){
        float u = numerator / denominator;
        // BONUS : if u is between 0 and 1, the intersection point is between P1 and P2
        *intersection = l * u;
        return true;
    }
    return false;
}

