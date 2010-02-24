#include <vector>
#include <iostream>
#include "color/rgb.h"
#include "image/image.h"
#include "shapes/shape.h"
#include "shapes/instance.h"
#include "shapes/plane.h"
#include "shapes/triangle.h"
#include "shapes/unitsphere.h"
#include "util/matrix.h"
#include "ray.h"
#include "camera.h"
#include "scene.h"
#include "material.h"
#include "simpletexture.h"
#include "noisetexture.h"
#include "marbletexture.h"

using namespace std;

#define R 2

// Comment in and out in order to determine what is drawn
// #define BALLS
#define MARBLE

int main() {
#ifdef BALLS
	{
	float KA = 0.1f;
	float KD = 0.7f;
	float KS = 0.2f;
	float KT = 0.0f;
	float NI = 1.52f;
	float PHONG = 10.0f;
	
	Camera cam = Camera(Vector3D(2.5*R, -2.5*R, 3.5*R),
						Vector3D(0, 0, 1.5*R),
			    		Vector3D(0, 0, 1),
			    		80.0f, 1);

	// High ambient testing
	// Scene scene(cam, RGB(0, 0.1, 0.6), RGB(1, 1, 1), Vector3D(1, 0, 0) );
	// Correct values
	Scene scene(cam, RGB(0, 0.1, 0.6), RGB(0.1, 0.1, 0.1), Vector3D(1, 0, 0) );
	// Attenuation testing
	// Scene scene(cam, RGB(0, 0.1, 0.6), RGB(0.1, 0.1, 0.1), Vector3D(1, 0.02, 0) );
	
	scene.addLight(new Light(Vector3D(10,   0, 10), RGB(1, 1, 1)) );

    // geometry
    vector<Shape*> shapes;
    
	// Red ball
	Matrix trans = translate(-R*sqrt(3)/2, -R/2, R);
	trans = trans * scale(R, R, R);
	Instance *circle1 = new Instance(trans, new UnitSphere(
		new Material(KA, KD, KS, PHONG, KT, NI, 
					new SimpleTexture(RGB(0.6, 0.2, 0.1)))) );
	
	// Blue ball
	trans = translate(R*sqrt(3)/2, -R/2, R);
	trans = trans*scale(R, R, R);
	Instance *circle2 = new Instance(trans, new UnitSphere(
		new Material(KA, KD, KS, PHONG, KT, NI,
					new SimpleTexture(RGB(0.1, 0.2, 0.6)))) );
	
	// Teal ball
	trans = translate(0, R, R);
	trans = trans*scale(R, R, R);
	Instance *circle3 = new Instance(trans, new UnitSphere(
		new Material(KA, KD, KS, PHONG, KT, NI,
					new SimpleTexture(RGB(0.1, 0.8, 0.6)))) );
	
	// White ball
	trans = translate(0, 0, R*(2*sqrt(2/3.0)+1));
	trans = trans*scale(R, R, R);
	Instance *circle4 = new Instance(trans, new UnitSphere(
		new Material(KA, KD, KS, PHONG, 0.5f, NI,
					new SimpleTexture(RGB(0.8, 0.8, 0.9)))) );
	
	// Yellow plane
	Plane *plane = new Plane( Vector3D(0, 0, 1),
							  Vector3D(0, 0, 0),
							  		new Material(KA, KD, KS, PHONG, KT, NI,
												// 										   new MarbleTexture(
												// RGB(0.8, 0.0, 0.7),
												// RGB(0.4, 0.0, 0.3),
												// RGB(0.9, 0.0, 0.8),
												// 0.15f,
												// 1, 3))) ;
										new SimpleTexture(RGB(0.9, 0.9, 0.1))) );

			
	scene.addShape(circle1);
	scene.addShape(circle2);
	scene.addShape(circle3);
	scene.addShape(circle4);
	scene.addShape(plane);		

	Image im = scene.createImage(512, 512);

    im.writePPM(cout); 
	}    
#elif defined(MARBLE) 
	{
	float KA = 0.1f;
	float KD = 0.7f;
	float KS = 0.2f;
	float KT = 0.0f;
	float NI = 1.52f;
	float PHONG = 10.0f;
	
	Camera cam = Camera(Vector3D(2.5*R, -2.5*R, 3.5*R),
						Vector3D(0, 0, 1.5*R),
			    		Vector3D(0, 0, 1),
			    		80.0f, 1);

	// High ambient testing
	// Scene scene(cam, RGB(0, 0.1, 0.6), RGB(1, 1, 1), Vector3D(1, 0, 0) );
	// Correct values
	Scene scene(cam, RGB(0, 0.1, 0.6), RGB(0.1, 0.1, 0.1), Vector3D(1, 0, 0) );
	// Attenuation testing
	// Scene scene(cam, RGB(0, 0.1, 0.6), RGB(0.1, 0.1, 0.1), Vector3D(1, 0.02, 0) );
	
	scene.addLight(new Light(Vector3D(10,   0, 10), RGB(1, 1, 1)) );
	scene.addLight(new Light(Vector3D(10, -10, 10), RGB(1, 1, 1)) );

    // geometry
    vector<Shape*> shapes;
    
	// Sphere 1: Yellowish
	Matrix trans = translate(-R*sqrt(3)/2, -R/2, R);
	trans = trans * scale(R, R, R);
	Instance *circle1 = new Instance(trans, new UnitSphere(
		new Material(KA, KD, KS, PHONG, KT, NI, 
					new SimpleTexture(RGB(0.9, 0.9, 0.1)))) );
	
	// Sphere 2: Textured yellow
	trans = translate(R*sqrt(3)/2, -R/2, R);
	trans = trans*scale(R, R, R);
	Instance *circle2 = new Instance(trans, new UnitSphere(
			new Material(KA, KD, KS, PHONG, KT, NI,
					new MarbleTexture(
						RGB(0.8, 0.7, 0.0), // p0
						RGB(0.4, 0.3, 0.3), // p1
						RGB(0.9, 0.8, 0.0), // m0
						RGB(0.2, 0.1, 0.0), // m1
						Vector3D(0, 1, 1),
						0.5f,
						1, 4)) ) );
	
	// Sphere 3: Teal
	trans = translate(0, R, R);
	trans = trans*scale(R, R, R);
	Instance *circle3 = new Instance(trans, new UnitSphere(
		new Material(KA, KD, KS, PHONG, KT, NI,
					new SimpleTexture(RGB(0.1, 0.8, 0.6)))) );
	
	// Sphere 4: Textured teal
	trans = translate(0, 0, R*(2*sqrt(2/3.0)+1));
	trans = trans*scale(R, R, R);
	Instance *circle4 = new Instance(trans, new UnitSphere(
			new Material(0.1, 0.8, 0.1, PHONG, KT, NI,
					new MarbleTexture(
						RGB(0.0, 0.7, 0.8), // p0
						RGB(0.0, 0.3, 0.4), // m1
						RGB(0.0, 0.8, 0.9), // m0
						RGB(0.0, 0.1, 0.2), // m1
						Vector3D(0, 0, 1),
						0.5f,
						3, 5)) ) );
	
	// Plane: Purple stripes
	Plane *plane = new Plane( Vector3D(0, 0, 1),
							  Vector3D(0, 0, 0),
							  new Material(KA, KD, KS, PHONG, KT, NI,
										new MarbleTexture(
											RGB(0.8, 0.0, 0.7), // p0
											RGB(0.4, 0.0, 0.3), // m1
											RGB(0.9, 0.0, 0.8), // m0
											RGB(0.2, 0.0, 0.1), // m1
											Vector3D(0.2, 0.4, 1),
											0.3f,
											1, 3)) );

			
	scene.addShape(circle1);
	scene.addShape(circle2);
	scene.addShape(circle3);
	scene.addShape(circle4);
	scene.addShape(plane);		

	Image im = scene.createImage(512, 512);

    im.writePPM(cout); 
	}
#endif
}
