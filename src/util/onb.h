//  ONB.h
#ifndef _ONB_H_
#define _ONB_H_ 1

#include "vector3d.h"

class ONB
{
public:
   ONB() {};

   ONB(const Vector3D& a, const Vector3D& b, const Vector3D& c)
   { U = a; V = b; W = c; }

   void initFromU( const Vector3D& u );
   void initFromV( const Vector3D& v );
   void initFromW( const Vector3D& w );

   void set(const Vector3D& a, const Vector3D& b, const Vector3D& c)
   { U = a; V = b; W = c; }

   // Calculate the ONB from two vectors
   // The first one is the Fixed vector (it is just normalized)
   // The second is normalized and its direction can be adjusted
   void  initFromUV( const Vector3D& u, const Vector3D& v );
   void  initFromVU( const Vector3D& v, const Vector3D& u );

   void  initFromUW( const Vector3D& u, const Vector3D& w );
   void  initFromWU( const Vector3D& w, const Vector3D& u );

   void  initFromVW( const Vector3D& v, const Vector3D& w );
   void  initFromWV( const Vector3D& w, const Vector3D& v );
   
   friend istream &operator>>(istream &is, ONB &t);
   friend ostream &operator<<(ostream &os, const ONB &t);
   friend bool  operator==(const ONB& o1, const ONB &o2);

   // Get a component from the ONB basis
   Vector3D u() const { return U; }
   Vector3D v() const { return V; }
   Vector3D w() const { return W; }

   Vector3D U,V,W;
};

#endif // _ONB_H_
