#include "beztrianglemesh.h"
#include "shapes/triangle.h"

BezTriangleMesh::BezTriangleMesh(const vector<Vector3D>& _verts, int _width, Material* _mat) 
	: verts(_verts), width(_width), material(_mat) 
{
	x_min = x_max = verts[0].x();
	y_min = y_max = verts[0].y();
	z_min = z_max = verts[0].z();
	
	for (unsigned i = 1; i < verts.size(); i++) {
		x_min = (verts[i].x() < x_min ? verts[i].x() : x_min);
		y_min = (verts[i].y() < y_min ? verts[i].y() : y_min);
		z_min = (verts[i].z() < z_min ? verts[i].z() : z_min);
		
		x_max = (verts[i].x() > x_max ? verts[i].x() : x_max);
		y_max = (verts[i].y() > y_max ? verts[i].y() : y_max);
		z_max = (verts[i].z() > z_max ? verts[i].z() : z_max);	
	}		
}
	
bool BezTriangleMesh::hit(const Ray& r, float tmin, float tmax, HitRecord& record) const
{
	if(!boundingBox(0, 0).rayIntersect(r, tmin, tmax))
		return false;
	
	bool is_a_hit = false;
	int height = verts.size()/width;
	
	for (int j = 0; j < height - 1; j++) {
		for (int i = 0; i < width - 1; i++) {
			int index = i + (width * j);
			
			Triangle t1 = Triangle(verts[index], verts[index+1], 
								   verts[index+width], material);
			Triangle t2 = Triangle(verts[index+1], verts[index+width], 
								   verts[index+width+1], material);
								
			if (t1.hit(r, tmin, tmax, record)) {
				tmax = record.t;
				is_a_hit = true;
			}
			
			if (t2.hit(r, tmin, tmax, record)) {
				tmax = record.t;
				is_a_hit = true;
			}
		}
	}
	
	return is_a_hit;	
}

bool BezTriangleMesh::shadowHit(const Ray& r, float tmin, float tmax, Material*& mat) const
{
	if(!boundingBox(0, 0).rayIntersect(r, tmin, tmax))
		return false;
	
	int height = verts.size()/width;
	
	for (int j = 0; j <= height - 1; j++) {
		for (int i = 0; i < width - 1; i++) {
			int index = i + (width * j);
			
			Triangle t1 = Triangle(verts[index], verts[index+1], 
								   verts[index+width], material);
			Triangle t2 = Triangle(verts[index+1], verts[index+width], 
								   verts[index+width+1], material);
								
			if (t1.shadowHit(r, tmin, tmax, mat)) {
				return true;
			}
			
			if (t2.shadowHit(r, tmin, tmax, mat)) {
				return true;
			}
		}
	}
	
	return false;	
}

BBox BezTriangleMesh::boundingBox(float, float) const {
	return BBox(Vector3D(x_min, y_min, z_min), 
				Vector3D(x_max, y_max, z_max));
}
