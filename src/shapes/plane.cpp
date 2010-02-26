#include "plane.h"

Plane::Plane(const Vector3D& _N, const Vector3D& _P, Material *_mat) 
	: N(_N), P(_P), material(_mat) {}

bool Plane::hit(const Ray& r, double tmin, double tmax, HitRecord& record) const {
	double denom = dot(r.direction(), N);
	
	// Check for the ray being parallel
	if (denom < PARALLEL_EPS && denom > -PARALLEL_EPS) return false;
	
	// double D = dot(N, -P);
	
	double t = (dot(N, P - r.origin()) )/denom;
	// double tt = (dot(N, r.origin()) + D)/denom;
	// double t = (-D - dot(r.origin(), N))/denom;
	
	if (t >= tmin && t <= tmax) {
		record.p = record.texp = r.pointAtParameter(t);
        record.t = t;
		
		// FIXME: Planes can't be textured -- figure out texture coords for a plane at pt
		record.uv = Vector2D(0, 0);
		record.material = material;
		record.uvw.initFromW(N);
		
		return true;
	}
	return false;
}

bool Plane::shadowHit(const Ray& r, double tmin, double tmax, Material*& mat) const {
	mat = material;
	double denom = dot(r.direction(), N);
	
	// Check for the ray being parallel
	if (denom < PARALLEL_EPS && denom > PARALLEL_EPS) return false;
	
	double t = dot(N, P-r.origin())/denom;
	
	if (t >= tmin && t <= tmax) {
		return true;
	}
	return false;
}

// Note: Planes are infinite, so the bounding box should never even be used
BBox Plane::boundingBox(double time0, double time1) const { 
	return BBox(Vector3D(0, 0, 0), Vector3D(0, 0 ,0)); 
}
