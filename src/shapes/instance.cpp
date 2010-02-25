#include "instance.h"

Instance::Instance(Matrix trans, Matrix trans_inverse, Shape* _prim) 
	: M(trans), N(trans_inverse), prim(_prim) {}
	
Instance::Instance(Matrix trans, Shape* _prim) 
	: M(trans), N(trans), prim(_prim)
	{ N.invert(); }
	
bool Instance::hit(const Ray& r, float tmin, float tmax, HitRecord& rec) const
{
	Vector3D no = transformLoc(N, r.origin());
	Vector3D nd = transformVec(N, r.direction());
	
	Ray tray(no, nd);
	
	if (prim->hit(tray, tmin, tmax, rec))
	{
		rec.p = transformLoc(M, rec.p);
		Vector3D normal = transformVec(N.getTranspose(), rec.uvw.w());
		ONB uvw;
		uvw.initFromW(normal);
		rec.uvw = uvw;
		return true;
	}

	return false;
}

bool Instance::shadowHit(const Ray& r, float tmin, float tmax, Material*& mat) const
{
	Vector3D no = transformLoc(N, r.origin());
	Vector3D nd = transformVec(N, r.direction());
	
	Ray tray(no, nd);
	
	return prim->shadowHit(tray, tmin, tmax, mat);
}

// Note: Shouldn't be used, really. Let the bounding box check occur in the primitive
BBox Instance::boundingBox(float time0, float time1) const  {
	return prim->boundingBox(time0, time1);
}