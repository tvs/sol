// 
//  Project: raytracer
//  File name: image.h
//  Description: Simple image class that can handle PPMs from Realistic Ray Tracing, 
//      Second Edition, section 1.8.1. This should be broken apart so that other image
//      formats can be created more easily.
//  
//  @author Travis Hall, Copyright (C) 2010
//  @version 
//  
//  @see Realistic Ray Tracing (Shirley, Morley), Second Edition, section 1.8.2
// 

#ifndef _IMAGE_H_
#define _IMAGE_H_ 1

#include <cmath>
#include <string>
#include <ostream>
#include "color/rgb.h"

using namespace std;

class Image {
public:
    Image();
    Image(int width, int height);
    Image(int width, int height, RGB background);
    
    bool set(int x, int y, const RGB& color);
    void gammaCorrect(double gamma);
    
    void writePPM(ostream& out);
    void readPPM(string file_name);
    
private:
    RGB** raster;
    int nx;
    int ny;
};

#endif // _IMAGE_H_