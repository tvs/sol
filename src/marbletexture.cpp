#include "marbletexture.h"

// Book interpolation
// RGB MarbleTexture::value(const Vector2D& uv, const Vector3D& p) const
// {
// 	Vector3D fp = freq * p;
// 	
// 	float temp = scale*(turbulence3(fp.x(), fp.y(), fp.z(), octaves) + 1)/2.0;
// 	float t = 2.0 * fabs(sin(freq*dot(p, dir) + temp));
// 	
// 	// float temp = scale*turbulence3(fp.x(), fp.y(), fp.z(), octaves);
// 	// float t = (1 + sin(freq*dot(p, dir) + temp))/2.0;
// 	
// 	
// 	if (t < 1.0f)
// 		return (m0*t + (1.0f - t)*p1);
// 	else {
// 		t -= 1.0f;
// 		return (p0*t + (1.0f - t)*m0);
// 	}
// }

// Cubic Hermite spline
RGB MarbleTexture::value(const Vector2D& uv, const Vector3D& p) const
{
	Vector3D fp = freq*p;
	
	float temp = scale*turbulence3(fp.x(), fp.y(), fp.z(), octaves);
	float t = (1 + sin(freq*dot(fp, dir) + temp))/2.0;
	
	float tt = t*t;
	float ttt = tt*t;
	
	return 	(2*ttt - 3*tt + 1)*p0 + 2.0*(ttt - 2*tt + t)*m0 
		  + (-2*ttt + 3*tt)*p1    + 2.0*(ttt - tt)*m1;
	
}