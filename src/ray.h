#ifndef RAY_H
#define RAY_H

#include "util/vector3d.h"

class Ray  {
public:
    
    Ray() {}
    Ray(const Vector3D& a, const Vector3D& b) 
    { 
       data[0] = a; data[1] = b; 
       data[2] = Vector3D(1.0f / b.x(), 1.0f / b.y(), 1.0f / b.z());
       
       posneg[0] =  (data[1].x() > 0 ? 0 : 1);
       posneg[1] = posneg[0] ^ 1;
       
       posneg[2] =  (data[1].y() > 0 ? 0 : 1);
       posneg[3] = posneg[2] ^ 1;  
       
       posneg[4] =  (data[1].z() > 0 ? 0 : 1);
       posneg[5] = posneg[4] ^ 1;  
    }
    
    Ray(const Ray& r) {*this = r;}
    Vector3D origin() const {return data[0];}
    Vector3D direction() const {return data[1];}
    Vector3D invDirection() const {return data[2];}
    void setOrigin(const Vector3D& v) {data[0] = v;}
    void setDirection(const Vector3D& v) 
    {
       data[1] = v;
       data[2] = Vector3D(1.0f / v.x(), 1.0f / v.y(), 1.0f / v.z());
       
       posneg[0] =  (data[1].x() > 0 ? 0 : 1);
       posneg[1] = posneg[0] ^ 1;
       
       posneg[2] =  (data[1].y() > 0 ? 0 : 1);
       posneg[3] = posneg[2] ^ 1;  
       
       posneg[4] =  (data[1].z() > 0 ? 0 : 1);
       posneg[5] = posneg[4] ^ 1;  
    }
    Vector3D pointAtParameter(double t) const { return data[0] + t*data[1]; }

    Vector3D data[3];
    int posneg[6]; 
};

inline ostream &operator<<(ostream &os, const Ray &r) {
   os << "(" << r.origin() << ") + t("  << r.direction() << ")";
   return os;
}


#endif
