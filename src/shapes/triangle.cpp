#include "triangle.h"

Triangle::Triangle(const Vector3D& _p0, const Vector3D& _p1, 
    const Vector3D& _p2, Material *_mat)
        : p0(_p0), p1(_p1), p2(_p2), material(_mat) {}

Triangle::Triangle(const Vector3D& _p0, const Vector3D& _p1, const Vector3D& _p2,
				   const Vector2D& _u0, const Vector2D& _u1, const Vector2D& _u2,
				   Material *_mat)
		: p0(_p0), p1(_p1), p2(_p2), u0(_u0), u1(_u1), u2(_u2), material(_mat) {}
        
bool Triangle::hit(const Ray& r, float tmin, float tmax, HitRecord& record) const
{
    float tval;
    float A = p0.x() - p1.x();
    float B = p0.y() - p1.y();
    float C = p0.z() - p1.z();
    
    float D = p0.x() - p2.x();
    float E = p0.y() - p2.y();
    float F = p0.z() - p2.z();
    
    float G = r.direction().x();
    float H = r.direction().y();
    float I = r.direction().z();
    
    float J = p0.x() - r.origin().x();
    float K = p0.y() - r.origin().y();
    float L = p0.z() - r.origin().z();
    
    float EIHF = E*I - H*F;
    float GFDI = G*F - D*I;
    float DHEG = D*H - E*G;
    
    float denom = (A*EIHF + B*GFDI + C*DHEG);
    
    float beta = (J*EIHF + K*GFDI + L*DHEG) / denom;
    
    if (beta <= 0.0f || beta >= 1.0f) return false;
    
    float AKJB = A*K - J*B;
    float JCAL = J*C - A*L;
    float BLKC = B*L - K*C;
    
    float gamma = (I*AKJB + H*JCAL + G*BLKC) / denom;
    
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

bool Triangle::shadowHit(const Ray& r, float tmin, float tmax, Material*& mat) const {
	mat = material;
    float tval;
    float A = p0.x() - p1.x();
    float B = p0.y() - p1.y();
    float C = p0.z() - p1.z();
    
    float D = p0.x() - p2.x();
    float E = p0.y() - p2.y();
    float F = p0.z() - p2.z();
    
    float G = r.direction().x();
    float H = r.direction().y();
    float I = r.direction().z();
    
    float J = p0.x() - r.origin().x();
    float K = p0.y() - r.origin().y();
    float L = p0.z() - r.origin().z();
    
    float EIHF = E*I - H*F;
    float GFDI = G*F - D*I;
    float DHEG = D*H - E*G;
    
    float denom = (A*EIHF + B*GFDI + C*DHEG);
    
    float beta = (J*EIHF + K*GFDI + L*DHEG) / denom;
    
    if (beta <= 0.0f || beta >= 1.0f) return false;
    
    float AKJB = A*K - J*B;
    float JCAL = J*C - A*L;
    float BLKC = B*L - K*C;
    
    float gamma = (I*AKJB + H*JCAL + G*BLKC) / denom;
    
    if (gamma <= 0.0f || beta + gamma >= 1.0f) return false;
    
    tval = -(F*AKJB + E*JCAL + D*BLKC) / denom;
    
    return (tval >= tmin && tval <= tmax);
}