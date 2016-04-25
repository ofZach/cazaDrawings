#pragma once

#include "ofMain.h"

class Conics : public ofBaseApp{
public:
    Conics();
    
    // the cone
    ofNode apex;
    ofNode base;  // center of the base plane
    float radius; // radius of the base plane
    
    // functions
    void draw();
};