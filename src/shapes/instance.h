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
	bool hit(const Ray& r, double tmin, double tmax, HitRecord& rec) const;
	bool shadowHit(const Ray& r, double tmin, double tmax, Material*& mat) const;
	BBox boundingBox(double time0, double time1) const;
};

#endif // _INSTANCE_H_