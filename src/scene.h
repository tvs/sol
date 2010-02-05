#ifndef _SCENE_H_
#define _SCENE_H_ 1

#include <vector>
#include "camera.h"
#include "light.h"
#include "shapes/shape.h"
#include "image/image.h"

#define MAX_RECURSION_DEPTH 5
#define AIR_REFRACTION 1.0

// MAGIC NUMBERS
#define MAX_INTERSECTION_DISTANCE 100000.0f
#define MIN_INTERSECTION_DISTANCE 0.0003f

class Scene {
public:
	Camera cam;
	vector<Shape*> shapes;
	// TODO: Add in sampler for anti-aliasing
	vector<Light*> lights;
	RGB bgcolor;
	RGB ambient;
	Vector3D attenuation; // (const, linear, quadratic)
	
	Scene(const Camera& c, const RGB& color, const RGB& _ambient, const Vector3D _att)
		: cam(c), bgcolor(color), ambient(_ambient), attenuation(_att) {}
	
	void addShape(Shape *s);
	void addLight(Light *l);
	
	// Routine for beginning the image creation (does the ray tracing)
	Image createImage(int H, int W);
	
	// Recursive routine -- returns the color at the nearest intersection or the bgcolor
	// Also calculates shadows, etc. blah blah
	RGB traceRay(const Ray& r, float depth);
	
	float calculateAttenuation(const Vector3D& lightdir);
};

#endif