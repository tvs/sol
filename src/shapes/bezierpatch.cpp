#include "bezierpatch.h"

BezierPatch::BezierPatch(Vector3D (*vects)[4][4], int partitions, int u_detail, int v_detail, Material* _mat)
	: material(_mat)
{	
	// TODO: Find a better way to automatically determine partitioning from u and v detail
	int parts = pow(2.0, partitions);
	
	double du = 1.0/u_detail;
	double dv = 1.0/v_detail;
	
	u_detail /= parts;
	v_detail /= parts;
	
	vector<Shape*> meshes;
	// cerr << "u_detail: " << u_detail << " v_detail: " << v_detail << "\n";
	// cerr << "du: " << du << " dv: " << dv << "\n";
	for(int sHeight = 0; sHeight < parts; sHeight++) {
		// cerr << "SHEIGHT: " << sHeight << "\n";
		for (int sWidth = 0; sWidth < parts; sWidth++) {
			// cerr << "\tSWIDTH: " << sWidth << "\n";
			vector<Vector3D> verts;
			for (int j = 0; j <= v_detail; j++) {
				for (int i = 0; i <= u_detail; i++) {
					// cerr << "\t\t" << ((sWidth*u_detail)+i)*du << " " 
						 // << ((sHeight*v_detail)+j) * dv << "\n";
					verts.push_back(eval(((sWidth*u_detail)+i) * du, 
										 ((sHeight*v_detail)+j) * dv, vects));
					
					
				}
			}	
			meshes.push_back(new BezTriangleMesh(verts, u_detail+1, material));
		}
	}
	
	bvh = new BVH(meshes);
}

bool BezierPatch::hit(const Ray& r, double tmin, double tmax, HitRecord& record) const {
	return bvh->hit(r, tmin, tmax, record);
}

bool BezierPatch::shadowHit(const Ray& r, double tmin, double tmax, Material*& mat) const {
	return bvh->shadowHit(r, tmin, tmax, mat);
}

BBox BezierPatch::boundingBox(double time0, double time1) const {
	return bvh->boundingBox(time0, time1);
}

Vector3D lerp(double t, Vector3D& A, Vector3D & B) {
	return A*(1-t) + B*t;
}

Vector3D deCasteljau(double t, Vector3D (*P)[4]) {
	Vector3D P01 = lerp(t, (*P)[0], (*P)[1]);
	Vector3D P12 = lerp(t, (*P)[1], (*P)[2]);
	Vector3D P23 = lerp(t, (*P)[2], (*P)[3]);
	Vector3D P012 = lerp(t, P01, P12);
	Vector3D P123 = lerp(t, P12, P23);
	return lerp(t, P012, P123);
}

Vector3D eval(double u, double v, Vector3D (*P)[4][4]) {
	Vector3D Q[4];
	for (int j = 0; j <= 3; j++)
	  Q[j] = deCasteljau(u, &(*P)[j]);
	return deCasteljau(v, &Q);
}
