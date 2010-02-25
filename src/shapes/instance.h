#ifndef _INSTANCE_H_
#define _INSTANCE_H_ 1

#include "shape.h"
#include "util/matrix.h"

class Instance : public Shape {
public:
	Matrix M; // Matrix
	Matrix N; // Inverse transpose of M
	Shape *prim;
	
	Instance() {}
	~Instance() {}
	Instance(Matrix trans, Matrix trans_inverse, Shape *_prim);
	Instance(Matrix trans, Shape *_prim);
	bool hit(const Ray& r, float tmin, float tmax, HitRecord& rec) const;
	bool shadowHit(const Ray& r, float tmin, float tmax, Material*& mat) const;
	BBox boundingBox(float time0, float time1) const;
};

#endif // _INSTANCE_H_