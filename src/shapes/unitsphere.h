#ifndef _UNITSPHERE_H_
#define _UNITSPHERE_H_ 1

#include "shape.h"

#include "ray.h"
#include "util/vector3d.h"
#include "texture.h"

// Unit Sphere (center =  (0,0,0), r = 1)
class UnitSphere : public Shape {
public:
	Material *material;
    
    UnitSphere(Material* _mat);
    bool hit(const Ray& r, float tmin, float tmax, HitRecord& record) const;
    bool shadowHit(const Ray& r, float tmin, float tmax, Material*& mat) const;
};

#endif // _UNITSPHERE_H_