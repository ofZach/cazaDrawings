#include "Conics.h"

Conics::Conics(){
    radius = 50;
    focus = ofVec3f(0, 0, -200);
    apex.setPosition(0,0,0);
    apex.lookAt( focus );
    cone.setPosition(0,0,0);
    cone.lookAt( focus );

    base.setPosition(0, 0, -100);
    base.setParent( apex );
    
    for(int i = 0; i < RESOLUTION; i++){
        float angle = ofMap(i, 0, RESOLUTION, 0, TWO_PI);
        basePoints[i].setPosition( ofVec3f( radius *cos(angle), radius *sin(angle), base.getPosition().z ) );
        basePoints[i].setParent( apex );
    }
}

void Conics::drawIntersectionsWithPlane(ofVec3f planePt, ofVec3f planeNormal){
    ofVec3f intersect;
    ofVec3f ap = apex.getPosition() * cone.getLocalTransformMatrix();
    bool lastRound = false;
    int lastDraw = -1;
    ofPolyline polyline;
    int i;
    float thisU, lastU;
    for(i = 0; i < RESOLUTION; i++){
        ofVec3f bp = basePoints[i].getPosition() * cone.getLocalTransformMatrix();
        bool thisRound = linePlaneIntersect(ap, bp, planePt, planeNormal, &intersect, &thisU);
        if(thisRound && lastRound){
            // continue the line segment, only if on same side of cone
            if( ( thisU >= 0 && lastU >= 0) || (thisU < 0 && lastU < 0) )
                polyline.addVertex(intersect);
            else{
                polyline.draw();
                lastDraw = i;
                polyline.clear();
                polyline.addVertex(intersect);
            }
        }
        else if(thisRound){
            // new beginning to the polyline
            polyline.clear();
            polyline.addVertex(intersect);
        }
        else if(lastRound){
            // an ending to the current polyline
            polyline.draw();
            lastDraw = i;
        }
        lastRound = thisRound;
        lastU = thisU;
    }

    // if first and last are both draw, connect them, close the polyline loop
    ofVec3f firstPoint = basePoints[0].getPosition() * cone.getLocalTransformMatrix();
    bool firstIndex = linePlaneIntersect(ap, firstPoint, planePt, planeNormal, &intersect, &thisU);
    if(lastRound && firstIndex && ((thisU >= 0 && lastU >= 0) || (thisU < 0 && lastU < 0)) )
        polyline.addVertex(intersect);

//    if(lastDraw != i-1)
        polyline.draw();
}

void Conics::fillIntersectionsWithPlane(ofVec3f planePt, ofVec3f planeNormal){
    ofVec3f intersect;
    ofVec3f ap = apex.getPosition() * cone.getLocalTransformMatrix();
    bool lastRound = false;
    int lastDraw = -1;
    int i;
    float thisU, lastU;
    for(i = 0; i < RESOLUTION; i++){
        ofVec3f bp = basePoints[i].getPosition() * cone.getLocalTransformMatrix();
        bool thisRound = linePlaneIntersect(ap, bp, planePt, planeNormal, &intersect, &thisU);
        if(thisRound && lastRound){
            // continue the line segment, only if on same side of cone
            if( ( thisU >= 0 && lastU >= 0) || (thisU < 0 && lastU < 0) )
                ofVertex(intersect);
            else{
                ofEndShape();
                lastDraw = i;
                ofBeginShape();
                ofVertex(intersect);
            }
        }
        else if(thisRound){
            // new beginning to the polyline
            ofBeginShape();
            ofVertex(intersect);
        }
        else if(lastRound){
            // an ending to the current polyline
            ofEndShape();
            lastDraw = i;
        }
        lastRound = thisRound;
        lastU = thisU;
    }
    
    // if first and last are both draw, connect them, close the polyline loop
    ofVec3f firstPoint = basePoints[0].getPosition() * cone.getLocalTransformMatrix();
    bool firstIndex = linePlaneIntersect(ap, firstPoint, planePt, planeNormal, &intersect, &thisU);
    if(lastRound && firstIndex && ((thisU >= 0 && lastU >= 0) || (thisU < 0 && lastU < 0)) )
        ofVertex(intersect);
//        polyline.addVertex(intersect);
    
    //    if(lastDraw != i-1)

//    polyline.draw();
    ofEndShape(true);

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

bool Conics::linePlaneIntersect(ofVec3f linePt1, ofVec3f linePt2, ofVec3f planePt, ofVec3f planeN, ofVec3f *intersection, float *u){
    // line is defined by 2 points on a line
    // plane is defined by planeP point in the plane with normal planeN
    
    ofVec3f l = (linePt2 - linePt1);
    
    float numerator = dotProduct(planeN, (planePt - linePt1) );
    float denominator = dotProduct(planeN, l);
    if(denominator != 0){
        *u = numerator / denominator;
        // BONUS : if u is between 0 and 1, the intersection point is between P1 and P2
        *intersection = l * *u;
        return true;
    }
    return false;
}

