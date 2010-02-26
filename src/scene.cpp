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
	
	// Along the y-axis
	for (int y = 0; y < H; y++) {
		// Along the x-axis
        for (int x = 0; x < W; x++) {
			if (x == 80 && y == 351) {
				int xxx = 234123;
			}
			Ray r = cam.getRay(x, y, W, H);
			im.set(x, H-y-1, traceRay(r, MAX_RECURSION_DEPTH));
        }
    }
	return im;
}

RGB Scene::traceRay(const Ray& r, double depth) {
	HitRecord rec;
	Material *shadowMat;
	double tmax = MAX_INTERSECTION_DISTANCE;
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
		N.makeUnitVector();
		
		// Incoming view direction
		Vector3D v = r.direction();

		// (4) if d (dot) N < 0
		// 			entering <- true
		// 		else
		// 			entering <- false
		//			N <- -N (flip the surface normal)
		if (dot(v, N) < 0)
			entering = true;
		else {
			entering = false;
			N = -N;
		}
			
		RGB iLocal = RGB(0, 0, 0);
		RGB iReflect = RGB(0, 0, 0);
		RGB iTransmit = RGB(0, 0, 0);
		
		// Ambient is included even if occluded?
		double Ri = rec.material->KA * ambient.r();
		double Gi = rec.material->KA * ambient.g();
		double Bi = rec.material->KA * ambient.b();
		
		// Local illumination
		for (unsigned int j = 0; j < lights.size(); j++) {
			Light *light = lights[j];
			// Incoming light direction
			Vector3D inc = unitVector(light->pos - rec.p);
			bool occluded = false;
			
			// Shadow feeler ray
			double shadowFilter = 1.0;
			double tmax2 = MAX_INTERSECTION_DISTANCE;
			for (unsigned int m = 0; m < shapes.size(); m++) {
				if (shapes[m]->shadowHit(Ray(rec.p, inc), MIN_INTERSECTION_DISTANCE, 
										tmax2, shadowMat))
				{
					if (shadowMat->isTransmissive()) {
						shadowFilter -= shadowMat->KT;
					} else {
						occluded = true;
					}
				}
					
			}
			
			if (!occluded) {
				// Reflection direction		
				Vector3D ref = reflect(inc, N);
				ref.makeUnitVector();
				
				double spec = dot(ref, v);
				double nspec = 0;
				if (spec > 0) {
					nspec = pow(spec, rec.material->alpha);
				}
							
				double diffuse = rec.material->KD * dot(inc, N);
				double specular = rec.material->KS * nspec;
			
				double att = calculateAttenuation(rec.p - light->pos);
				
				double mult = shadowFilter*att;
			
				// (5) Compute I[local] using local illum model (Phong model)
				// TODO: Refactor so lighting model can be "dropped in"
				Ri += mult*((diffuse*light->color.r())+(specular*light->color.r()) );
				Gi += mult*((diffuse*light->color.g())+(specular*light->color.g()) );
				Bi += mult*((diffuse*light->color.b())+(specular*light->color.b()) );
			}
		}
		iLocal = RGB(Ri, Gi, Bi);
			
		// (6) if depth <= 0, return I[local]
		if (depth <= 0) return RGB(Ri, Gi, Bi);

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
		// TODO: add env variable for material stack
		if (rec.material->isTransmissive()) {
			double n1 = rec.material->KR;
			double n2 = AIR_REFRACTION;
			double n = (entering ? (n2/n1) : (n1/n2));
			
			double c1 = -dot(N, v);
			double check = 1 - (n*n) * (1 - (c1 * c1));

			if (check > 0) {
				double c2 = sqrtf(check);
			
				Vector3D Td = (n * v) + (n * c1 - c2) * N;
				// Td.makeUnitVector();
				
				Ray T = Ray(rec.p, Td);

				iTransmit += traceRay(T, depth-1);
			}
		}
		
		// Return (I[local] + ks * I[reflect] + kt * I[transmit]) * material_color
		return 	  (iLocal * rec.material->texture->value(rec.uv, rec.texp))
				+ (rec.material->KS * iReflect) 
				+ (rec.material->KT * iTransmit);
	}
	else // (2) if no intersections, return background color
		return bgcolor;
	
}

double Scene::calculateAttenuation(const Vector3D& lightdir) {
	double d =  lightdir.length();
	return 1.0/(attenuation.x() + attenuation.y()*d + attenuation.z()*d*d);
}
