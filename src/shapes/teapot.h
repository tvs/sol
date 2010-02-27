#ifndef TEAPOT_H
#define TEAPOT_H

#define TEA_NUMVERTS 269
#define TEA_NUMPATCHES 28

#include "shape.h"

extern double teapotVerts[TEA_NUMVERTS][3];
extern int teapotIndices[TEA_NUMPATCHES][4][4];

class Teapot : public Shape {
public:
	Material * material;
	vector<Shape*> patches;
	
	Teapot(int partitions, int u_detail, int v_detail, Material *_mat);
	bool hit(const Ray& r, double tmin, double tmax, HitRecord& record) const;
	bool shadowHit(const Ray& r, double tmin, double tmax, Material*& mat) const;
	BBox boundingBox(double time0, double time1) const;
};


#endif
