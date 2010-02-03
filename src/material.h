#ifndef _MATERIAL_H_
#define _MATERIAL_H_ 1

#include "util/vector3d.h"
#include "util/hitrecord.h"
#include "texture.h"

class HitRecord;

class Material {
public:
	float KA; // Ambient reflection
	float KD; // Diffuse reflection
	float KS; // Specular reflection
	float alpha; // Shininess coefficient
	float KT; 	// Transmission coefficient
	float KR; 	// Refraction coefficient
	
	Texture *texture;
	
	Material(float _ka, float _kd, float _ks,
	 		 float _alpha, float _kt, float _kr, Texture *_tex)
		: KA(_ka), KD(_kd), KS(_ks), alpha(_alpha), KT(_kt), KR(_kr), texture(_tex) {}
		
	Material(float _ka, float _kd, float _ks, float _alpha, Texture *_tex)
		: KA(_ka), KD(_kd), KS(_ks), alpha(_alpha), texture(_tex)
	{
		KT = 0.0f;
		KR = 1.0f; // Default "air"
	}
	
	bool isTransmissive() { return KT > 0.0f; }
	bool isReflective() { return KS > 0.0f; }
};

#endif