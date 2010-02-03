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
	float fovy, a;
	float h, w;
	
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
   
	Camera(Vector3D eye, Vector3D look_at, Vector3D up, float fov, float aspect) 
      		: e(eye), p(look_at), u(up), fovy(fov), a(aspect)
   	{
      	uvw.initFromWV( p-e, u );
		h = -2*tan((fovy/2)*PI/180);
		w = h * a;
   	}

   	Ray getRay(float i, float j, float H, float W) 
   	{
		float x = (w/(W-1))*i - (w/2);
		float y = (-h/(H-1))*j + (h/2);
	
		Vector3D o = e;
		Vector3D d = unitVector(x*uvw.U + y*uvw.V + uvw.W);
      	return Ray(o, d);
   	}
};

#endif