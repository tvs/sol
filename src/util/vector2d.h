// 
//  Project: raytracer
//  File name: vector2d.h
//  Description: Two-dimensional vector class using the Vector3 class from Realistic Ray 
//      Tracing, Second Edition as a template.
//      This is a seperate implementation rather than using a variable-length vector for
//      efficiency purposes.
//      Uses aggressive inlining to limit function call overhead and speed up access.
//  
//  @author Travis Hall, Copyright (C) 2010
//  @version 
//  
//  @see RRealistic Ray Tracing (Shirley, Morley), Second Edition, section 1.8.3
// 

#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>
#include <cstdlib>
#include <cassert>
#include <iostream>

using namespace std;

class Vector2D  {
public:
    
    Vector2D() { e[0]=0; e[1]=0; }
    Vector2D(float e0, float e1) {e[0]=e0; e[1]=e1; }
    float x() const { return e[0]; }
    float y() const { return e[1]; }
    void setX(float a) { e[0] = a; }
    void setY(float a) { e[1] = a; }

    Vector2D(const Vector2D &v) {
         e[0] = v.e[0]; e[1] = v.e[1]; 
    }

    const Vector2D& operator+() const { return *this; }
    Vector2D operator-() const { return Vector2D(-e[0], -e[1]); }
    float& operator[](int i) { assert ( i >= 0 && i < 2 ); return e[i]; }
    float operator[](int i) const { assert ( i >= 0 && i < 2 ); return e[i];}

    Vector2D& operator+=(const Vector2D &v2);
    Vector2D& operator-=(const Vector2D &v2);
    Vector2D& operator*=(const float t);
    Vector2D& operator/=(const float t);
    void scramble(); 

    
    float length() const { return sqrt(e[0]*e[0] + e[1]*e[1] ); }
    float squaredLength() const { return e[0]*e[0] + e[1]*e[1] ; }

    void makeUnitVector();

    float e[2];
};

inline void Vector2D::scramble()
{
   float _x;
   float _y = e[0];

   _x =  e[1] * 1234.12345054321f; 
   e[0] = _x - (int)_x;
   _y = _y * 7654.54321012345f;
   e[1] = _y - (int)_y;
}

inline bool operator==(const Vector2D &t1, const Vector2D &t2) {
   return ((t1[0]==t2[0])&&(t1[1]==t2[1]));
}

inline bool operator!=(const Vector2D &t1, const Vector2D &t2) {
   return ((t1[0]!=t2[0])||(t1[1]!=t2[1]));
}

inline istream &operator>>(istream &is, Vector2D &t) {
   is >> t[0] >> t[1];
   return is;
}

inline ostream &operator<<(ostream &os, const Vector2D &t) {
   os << t[0] << " " << t[1] ;
   return os;
}

inline Vector2D unitVector(const Vector2D& v) {
    float k = 1.0f / sqrt(v.e[0]*v.e[0] + v.e[1]*v.e[1]);
    return Vector2D(v.e[0]*k, v.e[1]*k);
}

inline void Vector2D::makeUnitVector() {
    float k = 1.0f / sqrt(e[0]*e[0] + e[1]*e[1]);
    e[0] *= k; e[1] *= k; 
}

inline Vector2D operator+(const Vector2D &v1, const Vector2D &v2) {
    return Vector2D( v1.e[0] + v2.e[0], v1.e[1] + v2.e[1]);
}

inline Vector2D operator-(const Vector2D &v1, const Vector2D &v2) {
    return Vector2D( v1.e[0] - v2.e[0], v1.e[1] - v2.e[1]);
}

inline Vector2D operator*(float t, const Vector2D &v) {
    return Vector2D(t*v.e[0], t*v.e[1]); 
}

inline Vector2D operator*(const Vector2D &v, float t) {
    return Vector2D(t*v.e[0], t*v.e[1]); 
}

inline Vector2D operator/(const Vector2D &v, float t) {
    return Vector2D(v.e[0]/t, v.e[1]/t); 
}


inline float dot(const Vector2D &v1, const Vector2D &v2) {
    return v1.e[0] *v2.e[0] + v1.e[1] *v2.e[1];
}



inline Vector2D& Vector2D::operator+=(const Vector2D &v){
    e[0]  += v.e[0];
    e[1]  += v.e[1];
    return *this;
}

inline Vector2D& Vector2D::operator-=(const Vector2D& v) {
    e[0]  -= v.e[0];
    e[1]  -= v.e[1];
    return *this;
}

inline Vector2D& Vector2D::operator*=(const float t) {
    e[0]  *= t;
    e[1]  *= t;
    return *this;
}

inline Vector2D& Vector2D::operator/=(const float t) {
    e[0]  /= t;
    e[1]  /= t;
    return *this;
}

#endif