#ifndef _HIT_RECORD_H_
#define _HIT_RECORD_H_ 1

#include "vector2d.h"
#include "vector3d.h"
#include "material.h"

class Material;

class HitRecord {
public:
    float t;
	Vector3D p;
	Vector3D texp;
	ONB uvw;
	Vector2D uv;
    Material *material;
};

#endif