#ifndef _TEXTURE_H_
#define _TEXTURE_H_ 1

#include "util/vector2d.h"
#include "util/vector3d.h"
#include "color/rgb.h"

class Texture {
public:
	// Vector2D is a UV coordinate, and the Vector3D is the 3D hit-point
	virtual RGB value(const Vector2D&, const Vector3D&) const = 0;
};

#endif