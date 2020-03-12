//
//  ofxOutputRedirector.hpp
//  MatrixStudy
//
//  Created by okuyama on 2020/03/05.
//
#pragma once
#include "ofMain.h"
#include <sys/stat.h>



class ofxOutputRedirector{
public:
    static const int bufNum = 3;
    void begin();
    void end();
    void readFromFile();
    void update();
    void draw();
    void Toggle_show();

    float alpha[2];
    int prevSize[2];
    
    
private:
    ofstream global_ofs[2];
    streambuf* oldCoutBuf;
    streambuf* oldCerrBuf;
    
    struct stat buf_stat[2];
    time_t  last_size;
    string path[2];//
    vector<vector<string> > outs; //0 stdout 1 errout
    int num_line = 22;
    bool show  = true;
    
};
