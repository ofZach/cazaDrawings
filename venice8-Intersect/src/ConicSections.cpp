#include "ofApp.h"

ConicSections::ConicSections(){
    
    topConeHidden = false;
    bottomConeHidden = false;
    
    topCone = ofConePrimitive(CONE_RADIUS, CONE_HEIGHT, CONE_RESOLUTION, 1);
    bottomCone = ofConePrimitive(CONE_RADIUS, -CONE_HEIGHT, CONE_RESOLUTION, 1);

    ofPoint origin = ofPoint(0, 0, 0);
    for(int i = 0;i < CONE_RESOLUTION; i++){
        ofxRay::Ray topRay, bottomRay;
        topRay.setStart( origin );
        bottomRay.setStart( origin );
        topRay.setEnd(ofPoint(CONE_RADIUS*cosf(2*M_PI*i/CONE_RESOLUTION),
                              CONE_HEIGHT,
                              CONE_RADIUS*sinf(2*M_PI*i/CONE_RESOLUTION)));
        bottomRay.setEnd(ofPoint(CONE_RADIUS*cosf(2*M_PI*i/CONE_RESOLUTION),
                              -CONE_HEIGHT,
                              CONE_RADIUS*sinf(2*M_PI*i/CONE_RESOLUTION)));
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
        for(int r = 0; r < topConeRays.size(); r++){
            ofVec3f topIntersect, bottomIntersect;

            if(!topConeHidden){
                if(planes[p].intersect(topConeRays[r], topIntersect))
                    topIntersections.push_back(topIntersect);
                else
                    topIntersections.push_back(ofVec3f(-1, -1, -1)); // code for out of bounds
            }
            if(!bottomConeHidden){
                if(planes[p].intersect(bottomConeRays[r], bottomIntersect))
                    bottomIntersections.push_back(bottomIntersect);
                else
                    bottomIntersections.push_back(ofVec3f(-1, -1, -1)); // code for out of bounds
            }
        }
        
        // convert intersections into polyline path (or multiple ones)
        // at the same time clip them against the top and bottom of the cones
        
        // each time we start a new plane, start a new polyline
        ofPolyline empty3;
        topIntersectionLines.push_back( empty3 );
        topLineIndex++; // if the line jumps cones or passes clipping planes- needs to start a new polyline
        for(int i = 0; i < topIntersections.size(); i++){
            if( !(topIntersections[i].x == -1 && topIntersections[i].y == -1 && topIntersections[i].z == -1) )                topIntersectionLines[ topLineIndex ].addVertex(topIntersections[i]);
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
            if( !(bottomIntersections[i].x == -1 && bottomIntersections[i].y == -1 && bottomIntersections[i].z == -1) )                bottomIntersectionLines[ bottomLineIndex ].addVertex(bottomIntersections[i]);
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
    if(topConeHidden && bottomConeHidden){
        return false;
    }
    else if (topConeHidden){
        if(yValue > 0 && yValue < CONE_HEIGHT)
            return true;
        return false;
    }
    else if (bottomConeHidden){
        if(yValue > -CONE_HEIGHT && yValue < 0)
            return true;
        return false;
    }
    else{
        if(yValue > -CONE_HEIGHT && yValue < CONE_HEIGHT)
            return true;
        return false;
    }
}
