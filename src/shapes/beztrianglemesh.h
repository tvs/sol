#ifndef _BEZ_TRIANGLE_MESH_H_
#define _BEZ_TRIANGLE_MESH_H_ 1

#include "util/vector3d.h"
#include "shapes/shape.h"
#include "material.h"
#include <vector>

/* Triangle mesh for the Bezier patch quadrants
 * Must know the "width" of the 2D array of triangles
 *
 * 3 --4 
 * | \| \
 * 0 _1 _2
 * Would have a "width" of 3 and a "height" of 2
 */
class BezTriangleMesh : public Shape {
public:
	vector<Vector3D> verts;
	int width;
	Material *material;
	
	double x_min, x_max;
	double y_min, y_max;
	double z_min, z_max;
	
	BezTriangleMesh(const vector<Vector3D>& _verts, int _width, Material *_mat);
	bool hit(const Ray& r, double tmin, double tmax, HitRecord& record) const;
	bool shadowHit(const Ray& r, double tmin, double tmax, Material*& mat) const;
	BBox boundingBox(double time0, double time1) const;
};

#endif