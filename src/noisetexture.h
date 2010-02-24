#ifndef _NOISE_TEXTURE_H_
#define _NOISE_TEXTURE_H_ 1

#include <cmath>
#include "texture.h"
#include "color/rgb.h"
#include "util/noise.h"

class NoiseTexture : public Texture
{
public:
	float scale;
	RGB c0, c1;
	
	NoiseTexture(float _scale = 1.0f)	
	{
		scale = _scale;
		c0 = RGB(0.8, 0.0, 0.0);
		c1 = RGB(0.0, 0.0, 0.0);
	}
	
	virtual RGB value(const Vector2D& uv, const Vector3D& p) const;
};


#endif