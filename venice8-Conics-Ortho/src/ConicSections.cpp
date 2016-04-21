#include "ofApp.h"

#define DEFAULT_CONE_RESOLUTION 500
#define DEFAULT_CONE_RADIUS 50
#define DEFAULT_CONE_HEIGHT 100

ConicSections::ConicSections(){
    
    topConeHidden = false;
    bottomConeHidden = false;
    
    coneHeight = DEFAULT_CONE_HEIGHT;
    coneRadius = DEFAULT_CONE_RADIUS;
    
    topCone = ofConePrimitive(coneRadius, coneHeight, DEFAULT_CONE_RESOLUTION, 1);
    bottomCone = ofConePrimitive(coneRadius, -coneHeight, DEFAULT_CONE_RESOLUTION, 1);
    
    ofPoint origin = ofPoint(0, 0, 0);
    for(int i = 0;i < DEFAULT_CONE_RESOLUTION; i++){
        ofxRay::Ray topRay, bottomRay;
        topRay.setStart( origin );
        bottomRay.setStart( origin );
        topRay.setEnd(ofPoint(coneRadius*cosf(2*M_PI*i/DEFAULT_CONE_RESOLUTION),
                              coneHeight,
                              coneRadius*sinf(2*M_PI*i/DEFAULT_CONE_RESOLUTION)));
        bottomRay.setEnd(ofPoint(coneRadius*cosf(2*M_PI*i/DEFAULT_CONE_RESOLUTION),
                                 -coneHeight,
                                 coneRadius*sinf(2*M_PI*i/DEFAULT_CONE_RESOLUTION)));
        topConeRays.push_back(topRay);
        bottomConeRays.push_back(bottomRay);
    }
}

ConicSections::ConicSections(float aConeHeight, float aConeRadius){
    
    topConeHidden = false;
    bottomConeHidden = false;
    
    coneHeight = aConeHeight;
    coneRadius = aConeRadius;
    
    topCone = ofConePrimitive(coneRadius, coneHeight, DEFAULT_CONE_RESOLUTION, 1);
    bottomCone = ofConePrimitive(coneRadius, -coneHeight, DEFAULT_CONE_RESOLUTION, 1);
    
    ofPoint origin = ofPoint(0, 0, 0);
    for(int i = 0;i < DEFAULT_CONE_RESOLUTION; i++){
        ofxRay::Ray topRay, bottomRay;
        topRay.setStart( origin );
        bottomRay.setStart( origin );
        topRay.setEnd(ofPoint(coneRadius*cosf(2*M_PI*i/DEFAULT_CONE_RESOLUTION),
                              coneHeight,
                              coneRadius*sinf(2*M_PI*i/DEFAULT_CONE_RESOLUTION)));
        bottomRay.setEnd(ofPoint(coneRadius*cosf(2*M_PI*i/DEFAULT_CONE_RESOLUTION),
                                 -coneHeight,
                                 coneRadius*sinf(2*M_PI*i/DEFAULT_CONE_RESOLUTION)));
        topConeRays.push_back(topRay);
        bottomConeRays.push_back(bottomRay);
    }
}



void ConicSections::drawIntersectionLines(vector<ofxRay::Plane> planes){
    
    topIntersectionLines.clear();
    bottomIntersectionLines.clear();
    ofPolyline empty1, empty2;;
    topIntersectionLines.push_back( empty1 );
    bottomIntersectionLines.push_back( empty2 );
    int topLineIndex = 0; // if the line jumps cones or passes clipping planes- needs to start a new polyline
    int bottomLineIndex = 0; // if the line jumps cones or passes clipping planes- needs to start a new polyline
    
    
    // gather all intersections with every plane
    for(int p = 0; p < planes.size();p++){
        // gather all intersections with this one plane
        vector<ofPoint> topIntersections;
        vector<ofPoint> bottomIntersections;
        // find all the intersections between the plane and the cones
        int firstValidTopStart = -1;
        int firstValidBottomStart = -1;
        for(int r = 0; r < topConeRays.size(); r++){
            ofVec3f topIntersect, bottomIntersect;
            
            if(!topConeHidden){
                if(planes[p].intersect(topConeRays[r], topIntersect)){
                    topIntersections.push_back(topIntersect);
                    if(firstValidTopStart == -1)
                        firstValidTopStart = r;
                }
                else
                    topIntersections.push_back(ofVec3f(-1, -1, -1)); // code for out of bounds
            }
            if(!bottomConeHidden){
                if(planes[p].intersect(bottomConeRays[r], bottomIntersect)){
                    bottomIntersections.push_back(bottomIntersect);
                    if(firstValidBottomStart == -1)
                        firstValidBottomStart = r;
                }
                else
                    bottomIntersections.push_back(ofVec3f(-1, -1, -1)); // code for out of bounds
            }
            // close path loop
            if(r == topConeRays.size()-1 && firstValidTopStart == 0){
                if(planes[p].intersect(topConeRays[0], topIntersect))
                    topIntersections.push_back(topIntersect);
            }
            if(r == bottomConeRays.size()-1 && firstValidBottomStart == 0){
                if(planes[p].intersect(bottomConeRays[0], bottomIntersect))
                    bottomIntersections.push_back(bottomIntersect);
            }
        }
        
        // convert intersections into polyline path (or multiple ones)
        // at the same time clip them against the top and bottom of the cones
        
        // each time we start a new plane, start a new polyline
        ofPolyline empty3;
        topIntersectionLines.push_back( empty3 );
        topLineIndex++; // if the line jumps cones or passes clipping planes- needs to start a new polyline
        for(int i = 0; i < topIntersections.size(); i++){
            if( !(topIntersections[i].x == -1 && topIntersections[i].y == -1 && topIntersections[i].z == -1) )
                topIntersectionLines[ topLineIndex ].addVertex(topIntersections[i]);
            else if (topIntersectionLines[ topLineIndex ].getVertices().size() > 0){
                ofPolyline polyline;
                topIntersectionLines.push_back(polyline);
                topLineIndex++;
            }
            //        cur.setClosed(true);
        }
        
        ofPolyline empty4;
        bottomIntersectionLines.push_back( empty4 );
        bottomLineIndex++; // if the line jumps cones or passes clipping planes- needs to start a new polyline
        for(int i = 0; i < bottomIntersections.size(); i++){
            if( !(bottomIntersections[i].x == -1 && bottomIntersections[i].y == -1 && bottomIntersections[i].z == -1) )
                bottomIntersectionLines[ bottomLineIndex ].addVertex(bottomIntersections[i]);
            else if (bottomIntersectionLines[ bottomLineIndex ].getVertices().size() > 0){
                ofPolyline polyline;
                bottomIntersectionLines.push_back(polyline);
                bottomLineIndex++;
            }
            //        cur.setClosed(true);
        }
        
        for(int i = 0; i < topIntersectionLines.size(); i++)
            topIntersectionLines[i].draw();
        for(int i = 0; i < bottomIntersectionLines.size(); i++)
            bottomIntersectionLines[i].draw();
    }
}

void ConicSections::drawIntersectionFills(vector<ofxRay::Plane> planes){
    
    //    topIntersectionLines.clear();
    //    bottomIntersectionLines.clear();
    ofPolyline topPolyline, bottomPolyline;
    //    topIntersectionLines.push_back( empty1 );
    //    bottomIntersectionLines.push_back( empty2 );
    
    // gather all intersections with every plane
    for(int p = 0; p < planes.size();p++){
        
        bottomPolyline.clear();
        topPolyline.clear();
        
        // gather all intersections with this one plane
        vector<ofPoint> topIntersections;
        vector<ofPoint> bottomIntersections;
        // find all the intersections between the plane and the cones
        for(int r = 0; r < topConeRays.size(); r++){
            ofVec3f topIntersect, bottomIntersect;
            
            if(!topConeHidden){
                if(planes[p].intersect(topConeRays[r], topIntersect)){
                    topIntersections.push_back(topIntersect);
                }
                else
                    topIntersections.push_back(ofVec3f(-1, -1, -1)); // code for out of bounds
            }
            if(!bottomConeHidden){
                if(planes[p].intersect(bottomConeRays[r], bottomIntersect)){
                    bottomIntersections.push_back(bottomIntersect);
                }
                else
                    bottomIntersections.push_back(ofVec3f(-1, -1, -1)); // code for out of bounds
            }
        }
        
        // convert intersections into polyline path (or multiple ones)
        // at the same time clip them against the top and bottom of the cones
        
        for(int i = 0; i < topIntersections.size(); i++){
            if( !(topIntersections[i].x == -1 && topIntersections[i].y == -1 && topIntersections[i].z == -1) )
                topPolyline.addVertex(topIntersections[i]);
        }
        topPolyline.close();
        
        for(int i = 0; i < bottomIntersections.size(); i++){
            if( !(bottomIntersections[i].x == -1 && bottomIntersections[i].y == -1 && bottomIntersections[i].z == -1) )
                bottomPolyline.addVertex(bottomIntersections[i]);
        }
        bottomPolyline.close();
        
        if(topPolyline.getVertices().size()){
            ofBeginShape();
            for( int i = 0; i < topPolyline.getVertices().size(); i++) {
                ofVertex(topPolyline.getVertices().at(i).x,
                         topPolyline.getVertices().at(i).y,
                         topPolyline.getVertices().at(i).z);
            }
            ofEndShape(true);
        }
        if(bottomPolyline.getVertices().size()){
            ofBeginShape();
            for( int i = 0; i < bottomPolyline.getVertices().size(); i++) {
                ofVertex(bottomPolyline.getVertices().at(i).x,
                         bottomPolyline.getVertices().at(i).y,
                         bottomPolyline.getVertices().at(i).z);
            }
            ofEndShape(true);
        }
    }
}


void ConicSections::drawCones(){
    
    if(!topConeHidden){
        ofPushMatrix();
        // this is needed to match the cone to the equation of the cone (the rays)
        ofTranslate(0, topCone.getHeight() * .5);
        topCone.draw();
        ofPopMatrix();
    }
    if(!bottomConeHidden){
        ofPushMatrix();
        // this is needed to match the cone to the equation of the cone (the rays)
        ofTranslate(0, bottomCone.getHeight() * .5);
        bottomCone.draw();
        ofPopMatrix();
    }
}

bool ConicSections::insideBounds(float yValue){
    return true;
    if(topConeHidden && bottomConeHidden){
        return false;
    }
    else if (topConeHidden){
        if(yValue > 0 && yValue < coneHeight)
            return true;
        return false;
    }
    else if (bottomConeHidden){
        if(yValue > -coneHeight && yValue < 0)
            return true;
        return false;
    }
    else{
        if(yValue > -coneHeight && yValue < coneHeight)
            return true;
        return false;
    }
}
