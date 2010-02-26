#ifndef _MARBLE_TEXTURE_H_
#define _MARBLE_TEXTURE_H_ 1

#include <cmath>
#include "texture.h"
#include "color/rgb.h"
#include "util/noise.h"
#include "util/vector3D.h"
#include "util/vector2D.h"

class MarbleTexture : public Texture
{
public:
	double freq, scale;
	int octaves;
	RGB p0, p1, m0, m1;
	Vector3D dir;
	
	MarbleTexture(double stripes_per_unit, double _scale = 5.0f, int _octaves = 8)
	{
		freq = M_PI * stripes_per_unit;
		scale = _scale;
		octaves = pow(2.0, _octaves);
		
		p0 = RGB(0.8, 0.8, 0.8);
		m0 = RGB(0.4, 0.2, 0.1);
		p1 = RGB(0.06, 0.04, 0.02);
		m1 = RGB(0.02, 0.01, 0.00);
		dir = Vector3D(1, 0, 0);
	}
	
	MarbleTexture(const RGB & _p0, const RGB & _p1, const RGB & _m0, const RGB & _m1,
				  const Vector3D & _dir,
				  double stripes_per_unit, double _scale = 5.0f, int _octaves = 8)
		: p0(_p0), p1(_p1), m0(_m0), m1(_m1), dir(_dir)
	{
		freq = M_PI * stripes_per_unit;
		scale = _scale;
		octaves = pow(2.0, _octaves);
	}
	
	virtual RGB value(const Vector2D& uv, const Vector3D &p) const;
	
};

#endif