//
//  pointLoader.cpp
//  pointLoader
//
//  Created by zach on 4/22/16.
//
//

#include "pointLoader.hpp"

#include "json.hpp"

using json = nlohmann::json;

//--------------------------------------------------------------
void pointLoader::setup(){
    parsejson("frameData.json");
    frame = 0;
}

void pointLoader::update(){
    frame++;
    frame %= ptData.size();
}

void pointLoader::draw(){
    for (int i = 0; i < ptData[frame].size(); i++){
        if(i < 60 && i > 48)
            ofSetColor(0, 255, 255);
        else
            ofSetColor(255, 255, 255);
        ofCircle(ptData[frame][i], 4);
    }
}


void pointLoader::parsejson(string fileName){
    std::ifstream input_file( ofToDataPath(fileName));
    nlohmann::json jsonDoc;
    jsonDoc << input_file;
    
    for (int i = 0; i < jsonDoc.size(); i++){
        vector < ofPoint > pts;
        cout << i << " "  << jsonDoc[i].size() << endl;
        
        for (int j = 0; j < jsonDoc[i].size(); j++){
            float x =  jsonDoc[i][j][0];
            float y =  jsonDoc[i][j][1];
            ofPoint pt(x,y);
            pts.push_back(pt);
        }
        ptData.push_back(pts);
        
    }

}