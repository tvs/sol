#ifndef _BEZIER_PATCH_H_
#define _BEZIER_PATCH_H_ 1

#include "shape.h"
#include "ray.h"
#include "util/vector3d.h"
#include "texture.h"
#include "beztrianglemesh.h"
#include "bvh.h"

// Cubic Bezier patch
class BezierPatch : public Shape {
public:
	Material *material;
	// BezTriangleMesh *mesh;
	BVH *bvh;
	
	BezierPatch(Vector3D (*vects)[4][4], int partitions, int u_detail, int v_detail, Material* _mat);
	bool hit(const Ray& r, float tmin, float tmax, HitRecord& record) const;
    bool shadowHit(const Ray& r, float tmin, float tmax, Material*& mat) const;
	BBox boundingBox(float time0, float time1) const;
};

Vector3D lerp(float t, Vector3D& A, Vector3D & B);
Vector3D deCasteljau(float t, Vector3D (*P)[4]);
Vector3D eval(float u, float v, Vector3D (*P)[4][4]);

#endif