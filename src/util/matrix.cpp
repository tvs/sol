/*****************************************************************************\
 *                                                                           *
 *  filename   : Matrix.cc                                                   *
 *  author     : R. Keith Morley                                             * 
 *  last mod   : 2/28/02                                                     *   
 *                                                                           *
 *                                                                           *   
\*****************************************************************************/           

#include "matrix.h"

Matrix::Matrix (const Matrix & right_op)
{  
   for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
         x[i][j] = right_op.x[i][j];
}

Matrix& Matrix::operator+= (const Matrix & right_op)
{  
   for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
         x[i][j] += right_op.x[i][j];
   return *this;
}  

Matrix& Matrix::operator-= (const Matrix & right_op)
{  
   for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
         x[i][j] -= right_op.x[i][j];
   return *this;
} 

Matrix& Matrix::operator*= (float right_op)
{  
   for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
         x[i][j] *= right_op;
   return *this;
} 

Matrix& Matrix::operator*= (const Matrix & right_op)
{
   Matrix ret = *this;

   for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
      {
	 float sum = 0;
	 for (int k = 0; k < 4; k++)
	    sum += ret.x[i][k] * right_op.x[k][j];
	 x[i][j] = sum;
      }
   return *this;
}

void Matrix::invert()
{
   float det = determinant();
   Matrix inverse;
   inverse.x[0][0]  = det3(x[1][1], x[1][2], x[1][3],
                           x[2][1], x[2][2], x[2][3],
                           x[3][1], x[3][2], x[3][3]) / det;
   inverse.x[0][1] = -det3(x[0][1], x[0][2], x[0][3],
                           x[2][1], x[2][2], x[2][3],
                           x[3][1], x[3][2], x[3][3]) / det;
   inverse.x[0][2]  = det3(x[0][1], x[0][2], x[0][3],
                           x[1][1], x[1][2], x[1][3],
                           x[3][1], x[3][2], x[3][3]) / det;
   inverse.x[0][3] = -det3(x[0][1], x[0][2], x[0][3],
                           x[1][1], x[1][2], x[1][3],
                           x[2][1], x[2][2], x[2][3]) / det;

   inverse.x[1][0] = -det3(x[1][0], x[1][2], x[1][3],
                           x[2][0], x[2][2], x[2][3],
                           x[3][0], x[3][2], x[3][3]) / det;
   inverse.x[1][1]  = det3(x[0][0], x[0][2], x[0][3],
                           x[2][0], x[2][2], x[2][3],
                           x[3][0], x[3][2], x[3][3]) / det;
   inverse.x[1][2] = -det3(x[0][0], x[0][2], x[0][3],
                           x[1][0], x[1][2], x[1][3],
                           x[3][0], x[3][2], x[3][3]) / det;
   inverse.x[1][3]  = det3(x[0][0], x[0][2], x[0][3],
                           x[1][0], x[1][2], x[1][3],
                           x[2][0], x[2][2], x[2][3]) / det;

   inverse.x[2][0]  = det3(x[1][0], x[1][1], x[1][3],
                           x[2][0], x[2][1], x[2][3],
                           x[3][0], x[3][1], x[3][3]) / det;
   inverse.x[2][1] = -det3(x[0][0], x[0][1], x[0][3],
                           x[2][0], x[2][1], x[2][3],
                           x[3][0], x[3][1], x[3][3]) / det;
   inverse.x[2][2]  = det3(x[0][0], x[0][1], x[0][3],
                           x[1][0], x[1][1], x[1][3],
                           x[3][0], x[3][1], x[3][3]) / det;
   inverse.x[2][3] = -det3(x[0][0], x[0][1], x[0][3],
                           x[1][0], x[1][1], x[1][3],
                           x[2][0], x[2][1], x[2][3]) / det;

  
   inverse.x[3][0] = -det3(x[1][0], x[1][1], x[1][2],
                           x[2][0], x[2][1], x[2][2],
                           x[3][0], x[3][1], x[3][2]) / det;
   inverse.x[3][1] =  det3(x[0][0], x[0][1], x[0][2],
                           x[2][0], x[2][1], x[2][2],
                           x[3][0], x[3][1], x[3][2]) / det;
   inverse.x[3][2] = -det3(x[0][0], x[0][1], x[0][2],
                           x[1][0], x[1][1], x[1][2],
                           x[3][0], x[3][1], x[3][2]) / det;
   inverse.x[3][3] =  det3(x[0][0], x[0][1], x[0][2],
                           x[1][0], x[1][1], x[1][2],
                           x[2][0], x[2][1], x[2][2]) / det;   
   
  *this = inverse;
   
}

Matrix Matrix::getInverse()const
{
   Matrix ret = *this;
   ret.invert();
   return ret;
}  

void Matrix::transpose()
{
   for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
      {
	 float temp = x[i][j];
	 x[i][j] = x[j][i];
	 x[j][i] = temp;
      }
}

Matrix Matrix::getTranspose()const
{
   Matrix ret = *this;
   ret.transpose();

   return ret;
}

Vector3D transformLoc(const Matrix& left_op, const Vector3D& right_op)
{ return left_op * right_op; }

Vector3D transformVec(const Matrix& left_op, const Vector3D& right_op)
{
   Vector3D ret;

   ret[0] = right_op[0] * left_op.x[0][0] + right_op[1] * left_op.x[0][1] + 
            right_op[2] * left_op.x[0][2];
   ret[1] = right_op[0] * left_op.x[1][0] + right_op[1] * left_op.x[1][1] +
            right_op[2] * left_op.x[1][2];
   ret[2] = right_op[0] * left_op.x[2][0] + right_op[1] * left_op.x[2][1] +
            right_op[2] * left_op.x[2][2];
   
   return ret;
   
}
   
Matrix zeroMatrix ()
{
   Matrix ret;
   for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
         ret.x[i][j] = 0.0;
   return ret;
}   
	 
Matrix identityMatrix()
{
   Matrix ret;
   ret.x[0][0] = 1.0;
   ret.x[0][1] = 0.0;
   ret.x[0][2] = 0.0;
   ret.x[0][3] = 0.0;
   ret.x[1][0] = 0.0;
   ret.x[1][1] = 1.0;
   ret.x[1][2] = 0.0;
   ret.x[1][3] = 0.0;
   ret.x[2][0] = 0.0;
   ret.x[2][1] = 0.0;
   ret.x[2][2] = 1.0;
   ret.x[2][3] = 0.0;
   ret.x[3][0] = 0.0;
   ret.x[3][1] = 0.0;
   ret.x[3][2] = 0.0;
   ret.x[3][3] = 1.0;
   return ret;
}
   
Matrix translate (float _x, float _y, float _z)
{
   Matrix ret = identityMatrix();
   
   ret.x[0][3] = _x;
   ret.x[1][3] = _y;
   ret.x[2][3] = _z;
   
   return ret;
}

// angle is in radians
Matrix rotateX (float angle)
{
   Matrix ret = identityMatrix();

   float cosine = cos(angle);
   float sine   = sin(angle);

   ret.x[1][1] = cosine;
   ret.x[1][2] =  -sine;
   ret.x[2][1] =   sine;
   ret.x[2][2] = cosine;

   return ret;
}

// angle is in radians
Matrix rotateY (float angle)
{  
   Matrix ret = identityMatrix();

   float cosine = cos(angle);
   float sine   = sin(angle);

   ret.x[0][0] = cosine;
   ret.x[0][2] =   sine;
   ret.x[2][0] =  -sine;
   ret.x[2][2] = cosine;

   return ret;
}
   
// angle is in radians
Matrix rotateZ (float angle)
{  
   Matrix ret = identityMatrix();

   float cosine = cos(angle);
   float sine   = sin(angle);

   ret.x[0][0] = cosine;
   ret.x[0][1] =  -sine;
   ret.x[1][0] =   sine;
   ret.x[1][1] = cosine;

   return ret;
}

// rotation is in radians about an arbitrary axis
Matrix
rotate(const Vector3D& axis, float angle)
{
   Vector3D _axis = unitVector(axis);
   Matrix ret;
   float x = _axis.x();
   float y = _axis.y();
   float z = _axis.z();
   float cosine = cos(angle);
   float sine = sin(angle);
   float t   = 1 - cosine;   

   ret.x[0][0] = t * x * x + cosine;
   ret.x[0][1] = t * x * y - sine * y;
   ret.x[0][2] = t * x * z + sine * y;
   ret.x[0][3] = 0.0;
   
   ret.x[1][0] = t * x * y + sine * z;
   ret.x[1][1] = t * y * y + cosine;
   ret.x[1][2] = t * y * z - sine * x;
   ret.x[1][3] = 0.0;
   
   ret.x[2][0] = t * x * z - sine * y;
   ret.x[2][1] = t * y * z + sine * x;
   ret.x[2][2] = t * z * z + cosine;
   ret.x[2][3] = 0.0;
   
   ret.x[3][0] = 0.0;
   ret.x[3][1] = 0.0;
   ret.x[3][2] = 0.0;
   ret.x[3][3] = 1.0;

   return ret;
}

Matrix scale(float _x, float _y, float _z)
{
   Matrix ret = zeroMatrix();

   ret.x[0][0] = _x;
   ret.x[1][1] = _y;
   ret.x[2][2] = _z;
   ret.x[3][3] = 1.0;

   return ret;
}
   
// creates viewing Matrix that so the ey is at xyz origin looking down the -z axis
Matrix 
viewMatrix(const Vector3D& eye, const Vector3D& gaze, const Vector3D& up)
{
   Matrix ret = identityMatrix();

   // create an orthoganal basis from parameters
   Vector3D w = -(unitVector(gaze));
   Vector3D u = unitVector(cross(up, w));
   Vector3D v = cross(w, u);

   // rotate orthoganal basis to xyz basis
   ret.x[0][0] = u.x();
   ret.x[0][1] = u.y();
   ret.x[0][2] = u.z();
   ret.x[1][0] = v.x();
   ret.x[1][1] = v.y();
   ret.x[1][2] = v.z();
   ret.x[2][0] = w.x();
   ret.x[2][1] = w.y();
   ret.x[2][2] = w.z();
   
   // translare eye to xyz origin
   Matrix move = identityMatrix();
   move.x[0][3] = -(eye.x());
   move.x[1][3] = -(eye.y());
   move.x[2][3] = -(eye.z());

   ret = ret * move;
   return ret;
}
      
Matrix operator+ (const Matrix & left_op, const Matrix & right_op)
{
   Matrix ret;

   for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
	 ret.x[i][j] = left_op.x[i][j] + right_op.x[i][j];
   
   return ret;
}

Matrix operator- (const Matrix & left_op, const Matrix & right_op)
{
   Matrix ret;

   for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
         ret.x[i][j] = left_op.x[i][j] - right_op.x[i][j];
   
   return ret;
}

Matrix operator* (const Matrix & left_op, float right_op)
{
   Matrix ret;

   for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
         ret.x[i][j] = left_op.x[i][j] * right_op;
   
   return ret;
}

Matrix operator* (const Matrix & left_op, const Matrix & right_op)
{
   Matrix ret;

   for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
      {
	 float subt = 0.0;
	 for (int k = 0; k < 4; k++)
	    subt += left_op.x[i][k] * right_op.x[k][j];
	 ret.x[i][j] = subt;
      }

   return ret;
}

// transform a vector by matrix
Vector3D operator* (const Matrix & left_op, const Vector3D& right_op)
{
   Vector3D ret;
   float temp;

   ret[0] = right_op[0] * left_op.x[0][0] + right_op[1] * left_op.x[0][1] + 
              right_op[2] * left_op.x[0][2] +               left_op.x[0][3];
   ret[1] = right_op[0] * left_op.x[1][0] + right_op[1] * left_op.x[1][1] +
              right_op[2] * left_op.x[1][2] +               left_op.x[1][3];
   ret[2] = right_op[0] * left_op.x[2][0] + right_op[1] * left_op.x[2][1] +
              right_op[2] * left_op.x[2][2] +               left_op.x[2][3];
   temp   = right_op[0] * left_op.x[3][0] + right_op[1] * left_op.x[3][1] +
              right_op[2] * left_op.x[3][2] +               left_op.x[3][3];
   
   ret /= temp;
   return ret;
}
   
ostream & operator<< (ostream & out, const Matrix & right_op)
{
   for (int i = 0; i < 4; i++)
   {
      for (int j = 0; j < 4; j++)
	 out << setprecision(3) << setw(10) << right_op.x[i][j];
      out << endl;
   }
   return out;
}

float Matrix::determinant()
{
   float det;
   det  = x[0][0] * det3(x[1][1], x[1][2], x[1][3], 
                         x[2][1], x[2][2], x[2][3], 
                         x[3][1], x[3][2], x[3][3]);
   det -= x[0][1] * det3(x[1][0], x[1][2], x[1][3],
                         x[2][0], x[2][2], x[2][3],
                         x[3][0], x[3][2], x[3][3]);
   det += x[0][2] * det3(x[1][0], x[1][1], x[1][3],
                         x[2][0], x[2][1], x[2][3],
                         x[3][0], x[3][1], x[3][3]);
   det -= x[0][3] * det3(x[1][0], x[1][1], x[1][2],
                         x[2][0], x[2][1], x[2][2],
                         x[3][0], x[3][1], x[3][2]);
   return det;
}
	 
