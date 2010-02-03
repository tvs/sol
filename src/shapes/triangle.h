#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_ 1

#include "shape.h"
#include "util/vector3d.h"
#include "texture.h"
#include "ray.h"

class Triangle : public Shape {
public:
    Vector3D p0;
    Vector3D p1;
    Vector3D p2;

	Vector2D u0;
   	Vector2D u1;
   	Vector2D u2;
    
    Material *material;
    
   	Triangle(const Vector3D& _p0, const Vector3D& _p1, 
            const Vector3D& _p2, Material *_mat);

   	Triangle(const Vector3D& _p0, const Vector3D& _p1, const Vector3D& _p2,
            const Vector2D& _u0, const Vector2D& _u1, const Vector2D& _u2,   
            Material *_mat);
	bool hit(const Ray& r, float tmin, float tmax, HitRecord &record) const;
    bool shadowHit(const Ray& r, float tmin, float tmax, Material*& mat) const;
};

#endif // _TRIANGLE_H_