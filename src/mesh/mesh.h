#ifndef _MESH_H_
#define _MESH_H_ 1

#include <vector>
#include "util/vector3d.h"

namespace Winged {
	
	struct Vertex;
	struct Face;
	
	struct Edge {
		Vertex *v;
		Face *f;
		Edge *prev, *next;
		Edge *sym;
	};
	
	struct Vertex {
		Vector3D pos;
		Edge *e;
	};
	
	struct Face {
		Edge *e;
	};
	
	class Mesh {
	protected:
		std::vector<Winged::Edge*> edges;
		std::vector<Winged::Face*> faces;
		std::vector<Winged::Vertex*> verts;
	public:
		// 
		// Assumes closed, 2-manifold surface.
		// All face indices are counter clockwise (or all clockwise).
		// 
		Mesh(const std::vector<Vector3D>& V,
			 const std::vector<std::vector<int> >& F);
	};
}

#endif // _MESH_H_