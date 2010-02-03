#include "scene.h"
#include <cmath>

void Scene::addShape(Shape *s) {
	shapes.push_back(s);
}

void Scene::addLight(Light *l) {
	lights.push_back(l);
}

Image Scene::createImage(int H, int W) {
	Image im(H, W);
	
	for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
			// Use the sampler to determine I and J and average the resultant pixels
	    	Ray r = cam.getRay(i, j, H, W);
			im.set(i, j, traceRay(r, MAX_RECURSION_DEPTH));
        }
    }
	return im;
}

RGB Scene::traceRay(const Ray& r, float depth) {
	HitRecord rec;
	Material *shadowMat;
	float tmax = MAX_INTERSECTION_DISTANCE;
	bool is_a_hit = false;
	
	for (unsigned int k = 0; k < shapes.size(); k++) {
		
		// (1) Find the 1st object in the scene that is intersected by r
		// (3) Fetch the surface normal N and material prop. at intersection point
		if (shapes[k]->hit(r, MIN_INTERSECTION_DISTANCE, tmax, rec)) {
			tmax = rec.t;
			is_a_hit = true;
		}
	}
	
	if (is_a_hit) {
		bool entering;
		Vector3D N = rec.uvw.W;

		// (4) if d (dot) N < 0
		// 			entering <- true
		// 		else
		// 			entering <- false
		//			N <- -N (flip the surface normal)
		if (dot(r.direction(), N) < 0)
			entering = true;
		else {
			entering = false;
			N = -N;
		}
			
		RGB iLocal = RGB(0, 0, 0);
		RGB iReflect = RGB(0, 0, 0);
		RGB iTransmit = RGB(0, 0, 0);
		
		// Ambient is included even if occluded?
		float Ri = rec.material->KA * ambient.r();
		float Gi = rec.material->KA * ambient.g();
		float Bi = rec.material->KA * ambient.b();
		
		// Incoming view direction
		Vector3D v = unitVector(rec.p - cam.e);
		
		// Local illumination
		for (unsigned int j = 0; j < lights.size(); j++) {
			// Incoming light direction
			Vector3D inc = unitVector(lights[j]->pos - rec.p);
			bool occluded = false;
			
			// Shadow feeler ray
			float shadowFilter = 1.0;
			float tmax2 = MAX_INTERSECTION_DISTANCE;
			for (unsigned int m = 0; m < shapes.size(); m++) {
				if (shapes[m]->shadowHit(Ray(rec.p, inc), MIN_INTERSECTION_DISTANCE, 
										tmax2, shadowMat))
				{
					if (shadowMat->isTransmissive()) {
						shadowFilter = shadowMat->KT;
					} else {
						occluded = true;
					}
				}
					
			}
			
			if (!occluded) {
				Light *light = lights[j];
				// Reflection direction		
				Vector3D ref = reflect(inc, N);
				ref.makeUnitVector();
				
				float spec = dot(ref, v);
				float nspec = pow(spec, rec.material->alpha);
							
				float diffuse = rec.material->KD * dot(inc, N);
				float specular = rec.material->KS * nspec;
			
				float att = calculateAttenuation(rec.p - light->pos);
				
				float mult = shadowFilter*att;
			
				// (5) Compute I[local] using local illum model (Phong model)
				// TODO: Refactor so lighting model can be "dropped in"
				Ri += mult*((diffuse*light->color.r())+(specular*light->color.r()));
				Gi += mult*((diffuse*light->color.g())+(specular*light->color.g()));
				Bi += mult*((diffuse*light->color.b())+(specular*light->color.b()));
			}
		}
		iLocal = RGB(Ri, Gi, Bi);
			
		// (6) if depth <= 0, return I[local]
		if (depth <= 0) return RGB(Ri, Gi, Bi);// * rec.material->texture->value(rec.uv, rec.texp);

		// (7) I[reflect] <- (0, 0, 0)
		// 		if surface reflects light (rec.material->isReflective())
		// 			compute reflected Ray (p, ref)
		//			I[reflect] <- traceRay(R, depth-1, env)
		if (rec.material->isReflective()) {
			// Reflection direction		
			Vector3D ref = reflect(v, N);
			Ray R = Ray(rec.p, ref);
			iReflect += traceRay(R, depth-1);
		}

		// (8) I[transmit] <- (0, 0, 0)
		// 		if surface is transmissive (rec.material->isTransmissive())
		// 		compute transmitted ray T using Snell's law
		// 		if not total internal reflection
		// 			I[transmit] <- traceRay(T, depth-1, env')
		if (rec.material->isTransmissive()) {
			Vector3D D = r.direction();
			float n = rec.material->KR;
			float np = AIR_REFRACTION;
			
			float partOne = 1 - (entering ? ((n * n)/(np * np)) : ((np * np)/(n * n)));
			float partTwo = (1 - dot(D, N));
			
			float check = partOne * (partTwo * partTwo);
			if (check >= 0) {
				float snell = (entering ? n/np : np/n);
				Vector3D mid = ((D - N) * dot(N, D)) - N;
			
				float srt = sqrt(check);
			
				Vector3D Td = snell * mid * srt;
				Td.makeUnitVector();
				Ray T(rec.p, Td);

				iTransmit += traceRay(T, depth-1);
			}
		}

		// NOTE: env' depends on entering-flag
		//  May want to use a stack to push old env for later use
		
		// Return (I[local] + ks * I[reflect] + kt * I[transmit]) * material_color
		return 	  (iLocal * rec.material->texture->value(rec.uv, rec.texp))
				+ (rec.material->KS * iReflect) 
				+ (rec.material->KT * iTransmit);
	}
	else // (2) if no intersections, return background color
		return bgcolor;
	
}

float Scene::calculateAttenuation(const Vector3D& lightdir) {
	float d =  lightdir.length();
	return 1.0/(attenuation.x() + attenuation.y()*d + attenuation.z()*d*d);
}
