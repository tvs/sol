#include <map>
#include "mesh.h"

using namespace std;
using namespace Winged;

// 
// Euler's formula:
// 		F + V - E = 2
// 
Mesh::Mesh(const vector<Vector3D>& V,
	 	   const vector<vector<int> >& F) 
	: edges(2*(F.size() + V.size() - 2)),
	  faces(F.size()),
	  verts(V.size())
{
	map<pair<int, int>, Edge*> edgeMap;
	
	int ei = 0; // Index of current winged-edge
	
	for (unsigned fi = 0; fi < F.size(); fi++) {
		const vector<int>& f = F[fi];
		const unsigned fn = f.size();
		Face *wf = new Face;
		faces[fi] = wf;
		
		vector<Edge*> ee(fn);
		for (unsigned i = 0; i < fn; i++)
			edges[ei+i] = ee[i] = new Edge;
		
		wf->e = ee[0];
		ei += fn;
		
		for (unsigned i = 0; i < fn; i++) {
			const int v0 = f[i];
			const int v1 = f[(i+1) % fn];
			Edge *e = ee[i];
			
			if (verts[v0]) { // Found vertex
				e->v = verts[v0];
			} else { // Did *not* find vertex
				e->v = new Vertex;
				e->v->pos = V[v0];
				e->v->e = e;
				verts[v0] = e->v;
			}
			
			e->f = wf;
			e->next = ee[(i+1) % fn];
			e->prev = ee[(i-1+fn) % fn];
			
			map<pair<int, int>, Edge*>::iterator eiter = 
				edgeMap.find(pair<int, int>(v1, v0));
			
			if (eiter != edgeMap.end()) { // Symmetric edge already processed
				e->sym = eiter->second;
				either->second->sym = e;
			}		
		}		
	}
}