#ifndef _SIMPLE_TEXTURE_H_
#define _SIMPLE_TEXTURE_H_ 1

#include "texture.h"

class SimpleTexture : public Texture {
public:
	RGB color;
	SimpleTexture(RGB c) : color(c) {}
	virtual RGB value(const Vector2D&, const Vector3D&) const;
};

#endif