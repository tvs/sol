/******************************************************************************\
 *                                                                            *
 *  filename   : Matrix.h                                                     *
 *  author     : R. Keith Morley                                              *
 *  last mod   : 2/28/02                                                      * 
 *                                                                            *
 *  Matrix class for use in graphics applications                             *
 *                                                                            * 
\******************************************************************************/

#ifndef _MATRIX_H_
#define _MATRIX_H_ 1

#include <iostream>
#include <iomanip>
#include <cmath>

#include "vector3d.h"

class Matrix
{
public:
   Matrix() {}
   Matrix(const Matrix & orig);
   
   void invert();
   void transpose();
   Matrix getInverse()const;
   Matrix getTranspose()const;
   
   Matrix & operator+= (const Matrix& right_op);
   Matrix & operator-= (const Matrix& right_op);
   Matrix & operator*= (const Matrix& right_op);
   Matrix & operator*= (double right_op);

   friend Matrix operator- (const Matrix& left_op, const Matrix& right_op);
   friend Matrix operator+ (const Matrix& left_op, const Matrix& right_op);
   friend Matrix operator* (const Matrix& left_op, const Matrix& right_op);
   // matrix mult. performed left to right
   friend Vector3D operator* (const Matrix& left_op, const Vector3D& right_op);
   // transform vector by a matrix
   friend Matrix operator* (const Matrix & left_op, double right_op);

   friend Vector3D transformLoc(const Matrix& left_op, const Vector3D& right_op); 
   friend Vector3D transformVec(const Matrix& left_op, const Vector3D& right_op); 
   
   friend Matrix zeroMatrix();
   friend Matrix identityMatrix();
   friend Matrix translate(double _x, double _y, double _z);
   friend Matrix scale(double _x, double _y, double _z);
   friend Matrix rotate(const Vector3D& axis, double angle);
   friend Matrix rotateX(double angle);    //
   friend Matrix rotateY(double angle);    // More efficient than arbitrary axis
   friend Matrix rotateZ(double angle);    //
   friend Matrix viewMatrix(const Vector3D& eye, const Vector3D& gaze, 
         const Vector3D& up);
   friend ostream & operator<< (ostream& out, const Matrix& right_op);

   double determinant(); 
   double x[4][4];
};

// 3x3 matrix determinant -- helper function 
inline double det3 (double a, double b, double c, 
                   double d, double e, double f, 
                   double g, double h, double i)
{ return a*e*i + d*h*c + g*b*f - g*e*c - d*b*i - a*h*f; }

#endif   // _MATRIX_H_
