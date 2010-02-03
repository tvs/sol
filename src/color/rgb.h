// 
//  Project: raytracer
//  File name: rgb.h
//  Description: RGB color class from Realistic Ray Tracing, Second Edition, section 1.8.1
//      Note that there is no data protection, allowing direct access for faster
//      usage. Also note that there is no clamping, and that the user of the class
//      is responsible for maintaining it (for performance reasons).
//      Functions are inlined for a possible speedup, but it might be irrelevant and will
//      take some testing to determine.
//  
//  @author Travis Hall, Copyright (C) 2010
//  @version 0.1
//  
//  @see Realistic Ray Tracing (Shirley, Morley), Second Edition, section 1.8.1  
// 

#ifndef _RGB_H_
#define _RGB_H_ 1

#include <iostream>

using namespace std;

class RGB {
public:
    float _r;
    float _g;
    float _b;
    
    RGB() { _r = _g = _b = 0; }
    RGB(float red, float green, float blue);
    RGB(const RGB &original) { *this = original; }
    
    void setRed(float red)      { _r = red; }
    void setGreen(float green)  { _g = green; }
    void setBlue(float blue)    { _b = blue; }
    
    RGB& operator=(const RGB &right_op);
    RGB& operator+=(const RGB &right_op);
    RGB& operator*=(const RGB &right_op);
    RGB& operator/=(const RGB &right_op);
    RGB& operator*=(float right_op);
    RGB& operator/=(float right_op);
    
    RGB operator+()const { return *this; }
    RGB operator-()const { return RGB(-_r, -_g, -_b); }
    
    float r() const { return _r; }
    float g() const { return _g; }
    float b() const { return _b; }
    
    void clamp();
    
    // friend ostream& operator<<(ostream &out, const RGB &the_rgb);
    friend RGB operator*(const RGB& c, float f);
    friend RGB operator*(float f, const RGB& c);
    friend RGB operator/(const RGB& c, float f);
    friend RGB operator*(const RGB& c1, const RGB& c2);
    friend RGB operator/(const RGB& c1, const RGB& c2);
    friend RGB operator+(const RGB& c1, const RGB& c2);
};

inline RGB::RGB(float red, float green, float blue) : _r(red), _g(green), _b(blue) {}

inline RGB& RGB::operator+=(const RGB & right_op) { 
    *this = *this + right_op; 
    return *this;
}

inline RGB& RGB::operator*=(float right_op) {
    *this = *this * right_op;
    return *this;
}

inline RGB& RGB::operator/=(float right_op) {
    *this = *this / right_op;
    return *this;
}

inline RGB& RGB::operator*=(const RGB &right_op) {
    *this = *this * right_op;
    return *this;
}

inline RGB& RGB::operator/=(const RGB &right_op) {
    *this = *this / right_op;
    return *this;
}

inline RGB& RGB::operator=(const RGB &right_op) {
    _r = right_op._r;
    _g = right_op._g;
    _b = right_op._b;
    return *this;
}

inline void RGB::clamp() {
    if (_r > 1.0f) _r = 1.0f;
    if (_g > 1.0f) _g = 1.0f;
    if (_b > 1.0f) _b = 1.0f;
    if (_r < 0.0f) _r = 0.0f;
    if (_g < 0.0f) _g = 0.0f;
    if (_b < 0.0f) _b = 0.0f;
}

// inline ostream& operator<<(ostream &out, const RGB &the_rgb) {
//     out << the_rgb.r << ' '
//         << the_rgb.g << ' '
//         << the_rgb.b << ' ';
//     return out;
// }

inline RGB operator*(const RGB& c, float f) { return RGB(c._r*f, c._g*f, c._b*f); }

inline RGB operator*(float f, const RGB& c) { return RGB(c._r*f, c._g*f, c._b*f); }

inline RGB operator/(float f, const RGB& c) { return RGB(c._r/f, c._g/f, c._b/f); }

inline RGB operator*(const RGB& c1, const RGB& c2) { 
    return RGB(c1._r*c2._r, c1._g*c2._g, c1._b*c2._b);
}

inline RGB operator/(const RGB& c1, const RGB& c2) { 
    return RGB(c1._r/c2._r, c1._g/c2._g, c1._b/c2._b);
}

inline RGB operator+(const RGB& c1, const RGB& c2) { 
    return RGB(c1._r+c2._r, c1._g+c2._g, c1._b+c2._b);
}

#endif // _RGB_H_