#pragma once

#include "ofMain.h"



class pointLoader {
    
public:
    
    void setup();
    void update();
    void draw();
    
    vector <ofPoint> getFrameData(){
        return ptData[frame];
    }
    
    int frame;
    
    
    void parsejson(string fileName);
    vector < vector < ofPoint > > ptData;
    
    
    
};