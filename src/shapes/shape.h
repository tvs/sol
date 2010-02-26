#ifndef _SHAPE_H_
#define _SHAPE_H_ 1

#include "util/vector3d.h"
#include "util/vector2d.h"
#include "util/onb.h"
#include "util/hitrecord.h"
#include "ray.h"
#include "material.h"
#include "bbox.h"

class Shape {
public:
	Material *material;
	
    virtual bool hit(const Ray& r, double tmin, double tmax, HitRecord& record) const = 0;
    virtual bool shadowHit(const Ray &r, double tmin, double tmax, Material*& mat) const = 0;
	virtual BBox boundingBox(double time0, double time1) const = 0;
};

#endif // _SHAPE_H_