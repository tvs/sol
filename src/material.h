#ifndef _MATERIAL_H_
#define _MATERIAL_H_ 1

#include "util/vector3d.h"
#include "util/hitrecord.h"
#include "texture.h"

class HitRecord;

class Material {
public:
	double KA; // Ambient reflection
	double KD; // Diffuse reflection
	double KS; // Specular reflection
	double alpha; // Shininess coefficient
	double KT; 	// Transmission coefficient
	double KR; 	// Refraction coefficient
	
	Texture *texture;
	
	Material(double _ka, double _kd, double _ks,
	 		 double _alpha, double _kt, double _kr, Texture *_tex)
		: KA(_ka), KD(_kd), KS(_ks), alpha(_alpha), KT(_kt), KR(_kr), texture(_tex) {}
		
	Material(double _ka, double _kd, double _ks, double _alpha, Texture *_tex)
		: KA(_ka), KD(_kd), KS(_ks), alpha(_alpha), texture(_tex)
	{
		KT = 0.0f;
		KR = 1.0f; // Default "air"
	}
	
	bool isTransmissive() { return KT > 0.0f; }
	bool isReflective() { return KS > 0.0f; }
};

#endif