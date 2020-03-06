//
//  ofxOutputRedirector.cpp
//  MatrixStudy
//
//  Created by okuyama on 2020/03/05.
//

#include "ofxOutputRedirector.h"


void ofxOutputRedirector::begin(){
    vector<string> tmp;
    outs.push_back(tmp);
    outs.push_back(tmp);
    
    path[0] =ofFilePath::getAbsolutePath("cout.txt",true);
    path[1] =ofFilePath::getAbsolutePath("cerr.txt",true);
    global_ofs[0].open(path[0],std::ios::trunc);
    global_ofs[1].open(path[1],std::ios::trunc);
    
    stat(path[0] .c_str(), &buf_stat[0]);
    stat(path[1] .c_str(), &buf_stat[1]);
    cout<<"cout will redirect to /bin/data/cout.txt"<<endl;
    cout<<"cerr will redirect to /bin/data/cerr.txt"<<endl;
    oldCoutBuf = cout.rdbuf(global_ofs[0].rdbuf());
    oldCerrBuf =cerr.rdbuf(global_ofs[1].rdbuf());
    for(int i= 0;i<2;i++){
        alpha[i] = 1.0;
    }
}


void ofxOutputRedirector::end(){
    cout.rdbuf(oldCoutBuf);
    cerr.rdbuf(oldCerrBuf);
}
void ofxOutputRedirector::update(){
    
    
    outs[0].clear();
    outs[1].clear();
    readFromFile();
    for(int i= 0;i<2;i++){
    alpha[i] += (0.0-alpha[i])/10.0;
}
}

void ofxOutputRedirector::draw(){
    ofEnableAlphaBlending();
    ofSetColor(ofFloatColor(0.3,0.3,0.3,0.3));
       ofDrawRectangle(ofGetWidth()/4,0.0,ofGetWidth()/2*1.5,ofGetHeight());
    ofSetColor(ofFloatColor(0.0,1.0,0.0,alpha[0])); ofDrawRectangle(ofGetWidth()/4,0.0,ofGetWidth()/2*1.5,ofGetHeight()/2);
    ofSetColor(ofFloatColor(1.0,0.0,0.0,alpha[1])); ofDrawRectangle(ofGetWidth()/4,ofGetHeight()/2,ofGetWidth()/2*1.5,ofGetHeight()/2);
    
    ofSetColor(ofFloatColor(0.8,0.8,0.8,1.0));
    ofDrawLine(ofGetWidth()/4, 0.0,ofGetWidth()/4,ofGetHeight());
    ofDrawLine(ofGetWidth()/4, ofGetHeight()/2,ofGetWidth(),ofGetHeight()/2);
    
   
    ofSetColor(ofFloatColor(1.0));
    for(int i= 0;i<outs[0].size();i++){
        ofDrawBitmapString(outs[0][i],ofGetWidth()/4,11*(1+i));
    }
    for(int i= 0;i<outs[1].size();i++){
        ofDrawBitmapString(outs[1][i],ofGetWidth()/4,11*(i+1)+ofGetHeight()/2);
    }
    
    ofDisableAlphaBlending();
    
}



void ofxOutputRedirector::readFromFile(){
    vector<string> tmp;
    
    ofBuffer buffer  = ofBufferFromFile(string(path[0]));
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
        
        if(line.empty() == false) {
            tmp.push_back(line);
        }
    }
    
    //cout<<str<<endl;
    if(tmp.size()<num_line){
        for(int i = 0;i<tmp.size();i++){
            outs[0].push_back(tmp[i]);
        }
    }else{
        
        for(int i =tmp.size()- num_line;i<tmp.size();i++){
            outs[0].push_back(tmp[i]);
        }
    }
    if(prevSize[0] != tmp.size()){
        alpha[0] = 0.8;
    }
    prevSize[0] = tmp.size();
    tmp.clear();
    
    buffer  = ofBufferFromFile(string(path[1]));
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
        
        if(line.empty() == false) {
            tmp.push_back(line);
        }
    }
    //cout<<str<<endl;
    if(tmp.size()<num_line){
        for(int i = 0;i<tmp.size();i++){
            outs[1].push_back(tmp[i]);
        }
    }else{
        
        for(int i =tmp.size()- num_line;i<tmp.size();i++){
            outs[1].push_back(tmp[i]);
        }
    }
    if( prevSize[1] != tmp.size()){
        alpha[1] = 0.8;
    }
    prevSize[1] = tmp.size();
}



void ofxOutputRedirector::Toggle_show(){
    show = !show;
}
