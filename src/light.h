#ifndef _LIGHT_H_
#define _LIGHT_H_ 1

#include "color/rgb.h"

class Light {
public:
	Vector3D pos;
	RGB color;
	RGB ID; // Intensity of the diffuse light
	RGB IS; // Intensity of the specular light
	
	Light(const Vector3D& _pos, const RGB& _color, const RGB& _id, const RGB& _is)
		: pos(_pos), color(_color), ID(_id), IS(_is) {}
		
	Light(const Vector3D& _pos, const RGB& _color)
		: pos(_pos), color(_color), ID(_color), IS(_color) {}
		
};

#endif