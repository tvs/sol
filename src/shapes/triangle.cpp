#include "triangle.h"

Triangle::Triangle(const Vector3D& _p0, const Vector3D& _p1, 
    const Vector3D& _p2, Material *_mat)
        : p0(_p0), p1(_p1), p2(_p2), material(_mat) {}

Triangle::Triangle(const Vector3D& _p0, const Vector3D& _p1, const Vector3D& _p2,
				   const Vector2D& _u0, const Vector2D& _u1, const Vector2D& _u2,
				   Material *_mat)
		: p0(_p0), p1(_p1), p2(_p2), u0(_u0), u1(_u1), u2(_u2), material(_mat) {}
        
bool Triangle::hit(const Ray& r, double tmin, double tmax, HitRecord& record) const
{
	if(!boundingBox(0, 0).rayIntersect(r, tmin, tmax))
		return false;
	
    double tval;
    double A = p0.x() - p1.x();
    double B = p0.y() - p1.y();
    double C = p0.z() - p1.z();
    
    double D = p0.x() - p2.x();
    double E = p0.y() - p2.y();
    double F = p0.z() - p2.z();
    
    double G = r.direction().x();
    double H = r.direction().y();
    double I = r.direction().z();
    
    double J = p0.x() - r.origin().x();
    double K = p0.y() - r.origin().y();
    double L = p0.z() - r.origin().z();
    
    double EIHF = E*I - H*F;
    double GFDI = G*F - D*I;
    double DHEG = D*H - E*G;
    
    double denom = (A*EIHF + B*GFDI + C*DHEG);
    
    double beta = (J*EIHF + K*GFDI + L*DHEG) / denom;
    
    if (beta <= 0.0f || beta >= 1.0f) return false;
    
    double AKJB = A*K - J*B;
    double JCAL = J*C - A*L;
    double BLKC = B*L - K*C;
    
    double gamma = (I*AKJB + H*JCAL + G*BLKC) / denom;
    
    if (gamma <= 0.0f || beta + gamma >= 1.0f) return false;
    
    tval = -(F*AKJB + E*JCAL + D*BLKC) / denom;
    if(tval >= tmin && tval <= tmax) {
	
		record.p = record.texp = r.pointAtParameter(tval);
        record.t = tval;

		double alpha = 1.0 - beta - gamma;
		record.uv = Vector2D(alpha*u0.x() + beta*u1.x() + gamma*u2.x(),
							 alpha*u0.y() + beta*u1.y() + gamma*u2.y());
		record.material = material;
		
		Vector3D n = unitVector(cross((p1 - p0), (p2 - p0)));
		if (n.z() < -0.9999 || n.z() > 0.9999)
			record.uvw.initFromWV(n, Vector3D(0, 1, 0));
		else
			record.uvw.initFromWV(n, Vector3D(0, 0, 1));
        return true;
    }
    return false;
}

bool Triangle::shadowHit(const Ray& r, double tmin, double tmax, Material*& mat) const {
	if(!boundingBox(0, 0).rayIntersect(r, tmin, tmax))
		return false;
	
	mat = material;
    double tval;
    double A = p0.x() - p1.x();
    double B = p0.y() - p1.y();
    double C = p0.z() - p1.z();
    
    double D = p0.x() - p2.x();
    double E = p0.y() - p2.y();
    double F = p0.z() - p2.z();
    
    double G = r.direction().x();
    double H = r.direction().y();
    double I = r.direction().z();
    
    double J = p0.x() - r.origin().x();
    double K = p0.y() - r.origin().y();
    double L = p0.z() - r.origin().z();
    
    double EIHF = E*I - H*F;
    double GFDI = G*F - D*I;
    double DHEG = D*H - E*G;
    
    double denom = (A*EIHF + B*GFDI + C*DHEG);
    
    double beta = (J*EIHF + K*GFDI + L*DHEG) / denom;
    
    if (beta <= 0.0f || beta >= 1.0f) return false;
    
    double AKJB = A*K - J*B;
    double JCAL = J*C - A*L;
    double BLKC = B*L - K*C;
    
    double gamma = (I*AKJB + H*JCAL + G*BLKC) / denom;
    
    if (gamma <= 0.0f || beta + gamma >= 1.0f) return false;
    
    tval = -(F*AKJB + E*JCAL + D*BLKC) / denom;
    
    return (tval >= tmin && tval <= tmax);
}

BBox Triangle::boundingBox(double time0, double time1) const {
	const double epsilon = 0.00001f;
   	Vector3D min;
   	Vector3D max;

   	min.setX(p0.x() < p1.x() ? p0.x() : p1.x());
   	min.setY(p0.y() < p1.y() ? p0.y() : p1.y());
  	min.setZ(p0.z() < p1.z() ? p0.z() : p1.z());

   	min.setX(p2.x() < min.x() ? p2.x() : min.x());
   	min.setY(p2.y() < min.y() ? p2.y() : min.y());
   	min.setZ(p2.z() < min.z() ? p2.z() : min.z());

   	max.setX(p0.x() > p1.x() ? p0.x() : p1.x());
   	max.setY(p0.y() > p1.y() ? p0.y() : p1.y());
   	max.setZ(p0.z() > p1.z() ? p0.z() : p1.z());

   	max.setX(p2.x() > max.x() ? p2.x() : max.x());
   	max.setY(p2.y() > max.y() ? p2.y() : max.y());
   	max.setZ(p2.z() > max.z() ? p2.z() : max.z());

   	min.setX(min.x() - epsilon);
   	min.setY(min.y() - epsilon);
   	min.setZ(min.z() - epsilon);

   	max.setX(max.x() + epsilon);
   	max.setY(max.y() + epsilon);
   	max.setZ(max.z() + epsilon);
   	return BBox(min, max);
}