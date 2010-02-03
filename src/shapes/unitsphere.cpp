#include "unitsphere.h"

UnitSphere::UnitSphere(Material* _mat) : material(_mat) {}
    
bool UnitSphere::hit(const Ray& r, float tmin, float tmax, HitRecord& record) const
{
    double a = dot(r.direction(), r.direction());
    double b = 2*dot(r.direction(), r.origin());
    double c = dot(r.origin(), r.origin()) - 1;
    
    double discriminant = b*b - 4*a*c;
    
    // First check to see if ray intersects sphere
    if (discriminant > 0) {
        discriminant = sqrt(discriminant);
        double t = (-b - discriminant) / (2*a);
        
        // now check for valid interval
        if (t < tmin)
            t = (-b + discriminant) / (2*a);
        if (t < tmin || t > tmax)
            return false;
            
        // we have a valid hit
		record.p = record.texp = r.pointAtParameter(t);
        record.t = t;

		Vector3D n = record.p;
		float pi = 3.14159265359f;
		float theta = acos(0.9999f * n.z() );
		float sinTheta = sin(theta);
		float phi = acos (n.x() / (1.0001f * sinTheta) );
		
		if (n.y() < 0.0f) phi = 2*pi - phi;
		
		record.uv = Vector2D(phi/(2.0f*pi), 1.0f - theta/pi);
		record.material = material;
		record.uvw.initFromW(n);
		return true;
    }
    return false;
}

bool UnitSphere::shadowHit(const Ray& r, float tmin, float tmax, Material*& mat) const {
	mat = material;
    double a = dot(r.direction(), r.direction());
    double b = 2*dot(r.direction(), r.origin());
    double c = dot(r.origin(), r.origin()) - 1;
    
    double discriminant = b*b - 4*a*c;
    
    // First check to see if ray intersects sphere
    if (discriminant > 0) {
        discriminant = sqrt(discriminant);
        double t = (-b - discriminant) / (2*a);
        
        // now check for valid interval
        if (t < tmin)
            t = (-b + discriminant) / (2*a);
        if (t < tmin || t > tmax)
            return false;
            
        // we have a valid hit
        return true;
    }
    return false;
}