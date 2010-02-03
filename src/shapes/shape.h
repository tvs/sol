#ifndef _SHAPE_H_
#define _SHAPE_H_ 1

#include "util/vector3d.h"
#include "util/vector2d.h"
#include "util/onb.h"
#include "util/hitrecord.h"
#include "ray.h"
#include "material.h"

class Shape {
public:
	Material *material;
	
    virtual bool hit(const Ray& r, float tmin, float tmax, HitRecord& record) const = 0;
    virtual bool shadowHit(const Ray &r, float tmin, float tmax, Material*& mat) const = 0;
};

#endif // _SHAPE_H_