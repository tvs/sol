#ifndef _PLANE_H_
#define _PLANE_H_ 1

#include "shape.h"
#include "util/vector3d.h"
#include "texture.h"

#define PARALLEL_EPS 0.0000001

class Plane : public Shape {
public:
	Vector3D N;
	Vector3D P;
	Material *material;
	
	Plane(const Vector3D& _N, const Vector3D& _P, Material *_mat);
	bool hit(const Ray& r, float tmin, float tmax, HitRecord& record) const;
    bool shadowHit(const Ray& r, float tmin, float tmax, Material*& mat) const;
	BBox boundingBox(float time0, float time1) const;
};

#endif