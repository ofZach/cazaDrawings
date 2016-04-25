#include "Conics.h"

Conics::Conics(){
    apex.setPosition(0,0,100);
    apex.lookAt( ofVec3f(0, 0, 0));
}

void Conics::draw(){
    apex.transformGL();
    ofDrawCircle(ofPoint(0,0,-100), 50);
    apex.restoreTransformGL();
}