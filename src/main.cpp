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

using namespace std;

#define R 2

int main() {
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
	
	scene.addLight(new Light(Vector3D(10, 0, 10), RGB(1, 1, 1)) );
	// scene.addLight(new Light(Vector3D(-10, 0, 10), RGB(1, 1, 1)) );

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
										new SimpleTexture(RGB(0.9, 0.9, 0.1))) );

			
	scene.addShape(circle1);
	scene.addShape(circle2);
	scene.addShape(circle3);
	scene.addShape(circle4);
	scene.addShape(plane);		

	Image im = scene.createImage(512, 512);

    im.writePPM(cout);          
}
