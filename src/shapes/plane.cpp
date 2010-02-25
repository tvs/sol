#include "plane.h"

Plane::Plane(const Vector3D& _N, const Vector3D& _P, Material *_mat) 
	: N(_N), P(_P), material(_mat) {}

bool Plane::hit(const Ray& r, float tmin, float tmax, HitRecord& record) const {
	float denom = dot(r.direction(), N);
	
	// Check for the ray being parallel
	if (denom < PARALLEL_EPS && denom > -PARALLEL_EPS) return false;
	
	// float D = dot(N, -P);
	
	float t = (dot(N, P - r.origin()) )/denom;
	// float tt = (dot(N, r.origin()) + D)/denom;
	// float t = (-D - dot(r.origin(), N))/denom;
	
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

bool Plane::shadowHit(const Ray& r, float tmin, float tmax, Material*& mat) const {
	mat = material;
	float denom = dot(r.direction(), N);
	
	// Check for the ray being parallel
	if (denom < PARALLEL_EPS && denom > PARALLEL_EPS) return false;
	
	float t = dot(N, P-r.origin())/denom;
	
	if (t >= tmin && t <= tmax) {
		return true;
	}
	return false;
}

// Note: Planes are infinite, so the bounding box should never even be used
BBox Plane::boundingBox(float time0, float time1) const { 
	return BBox(Vector3D(0, 0, 0), Vector3D(0, 0 ,0)); 
}
