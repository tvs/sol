#include "image.h"
// #include <iostream>
#include <fstream>

using namespace std;

Image::Image() {}

Image::Image(int width, int height) {
    nx = width; ny = height;
    
    raster = new RGB*[nx];
    for (int i = 0; i < nx; i++)
        raster[i] = new RGB[ny];
}

Image::Image(int width, int height, RGB background) {
    nx = width; ny = height;
    
    raster = new RGB*[nx];
    for (int i = 0; i < nx; i++) {
        raster[i] = new RGB[ny];
        for (int j = 0; j < ny; j++) 
            raster[i][j] = background;
    }
}

bool Image::set(int x, int y, const RGB& color) {
    // Check out-of-bounds errors
    if (0 > x || x > nx) return false;
    if (0 > y || y > ny) return false;
    
    raster[x][y] = color;
    return true;
}

void Image::gammaCorrect(double gamma) {
    RGB temp;
    double power = 1.0/gamma;
    for (int i = 0; i < nx; i++) 
        for (int j = 0; j < ny; j++) {
            temp = raster[i][j];
            raster[i][j] = RGB(pow(temp.r(), power),
                               pow(temp.g(), power),
                               pow(temp.b(), power));
        }
}

void Image::writePPM(ostream& out) {
    // Output header
    out << "P6\n";
    out << nx << ' ' << ny << '\n';
    out << "255\n";
    
    int i, j;
    unsigned int ired, igreen, iblue;
    unsigned char red, green, blue;
    
    // output clamped [0, 255] values
    for (i = ny-1; i >= 0; i--)
        for(j = 0; j < nx; j++) {
            ired = (unsigned int) (256*raster[j][i].r());
            igreen = (unsigned int) (256*raster[j][i].g());
            iblue = (unsigned int) (256*raster[j][i].b());
            
            if (ired > 255) ired = 255;
            if (igreen > 255) igreen = 255;
            if (iblue > 255) iblue = 255;
            red = (unsigned char) (ired);
            green = (unsigned char) (igreen);
            blue = (unsigned char) (iblue);
            
            out.put(red);
            out.put(green);
            out.put(blue);
        }
}

// reads in a binary PPM
void Image::readPPM(string file_name) {
    // open stream to file
    ifstream in;
    in.open(file_name.c_str());
    if (!in.is_open()) {
        cerr << " ERROR -- Couldn't open file \'" << file_name << "\' .\n";
        exit(-1);
    }
    
    char ch, type;
    char red, green, blue;
    int i, j, cols, rows;
    int num;
    
    // read in header info
    in.get(ch);
    in.get(type);
    in >> cols >> rows >> num;
    
    nx = cols;
    ny = rows;
    
    // allocate raster
    raster = new RGB*[nx];
    for (i = 0; i < nx; i++) 
        raster[i] = new RGB[ny];
        
    // Clean up newline
    in.get(ch);
    
    // Store PPM pixel values in raster
    for (i = ny-1; i >= 0; i--)
        for (j = 0; j < nx; j++) {
            in.get(red);
            in.get(green);
            in.get(blue);
            raster[j][i] = RGB((double) ((unsigned char) red)/255.0,
                               (double) ((unsigned char) green)/255.0,
                               (double) ((unsigned char) blue)/255.0);
        }
}