#include "noisetexture.h"

RGB NoiseTexture::value(const Vector2D& uv, const Vector3D& p) const
{
	Vector3D sp = scale * p;
	float t = (1.0f + noise3(sp.x(), sp.y(), sp.z())) / 2.0f;
	return t*c0 + (1.0f - t)*c1;
}