#ifndef _CAMERA_H_
#define _CAMERA_H_ 1

#include "ray.h"
#include "util/onb.h"

#ifndef PI
#define PI 3.14159265
#endif

class Camera  
{
public:	
	Vector3D e, p, u;
   	ONB uvw;
	double fovy, a;
	double h, w;
	
   	Camera() {}
   	Camera(const Camera& orig)
   	{
      	e = orig.e;
		p = orig.p;
		u = orig.u;
		uvw = orig.uvw;
		fovy = orig.fovy;
		a = orig.a;
		h = orig.h;
		w = orig.w;
   	} 
   
	Camera(Vector3D eye, Vector3D look_at, Vector3D up, double fov, double aspect) 
      		: e(eye), p(look_at), u(up), fovy(fov), a(aspect)
   	{
		Vector3D D = unitVector(p - e);
		Vector3D R = unitVector(cross(D, u));
		Vector3D U = cross(R, D);
		
		uvw.set(R, U, D);
	
		h = 2*tan((fovy/2)*PI/180);
		w = h * a;
   	}

   	Ray getRay(double xx, double yy, double W, double H) 
   	{
		double x = (w/(W-1))*xx - (w/2.0);
		double y = ((-h)/(H-1))*yy + (h/2.0);
	
		Vector3D o = e;
		Vector3D d = x*uvw.U + y*uvw.V + uvw.W;
		Vector3D dd = unitVector(d);
		
      	return Ray(o, dd);
   	}
};

#endif