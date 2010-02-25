#ifndef _BEZIER_PATCH_H_
#define _BEZIER_PATCH_H_ 1

#include "shape.h"
#include "ray.h"
#include "util/vector3d.h"
#include "texture.h"

// Cubic Bezier patch
class BezierPatch : public Shape {
public:
	Material *material;	
	
	BezierPatch(Vector3D[4][4] vects, int u_detail, int v_detail) {
		// TODO: Bezier Patch
	}
};

#endif