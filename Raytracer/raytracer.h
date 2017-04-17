#ifndef _RAYTRACER_H
#define _RAYTRACER_H

#include "geometry.h"

class raytracer
{
	private:
		static void vec(float* a, float* b, float* c);
		static void cross_product(float* a, float* b, float* c);
		static float dot_product(float* a, float* b);
		static float distance_formula_3d(float x1, float y1, float z1, float x2, float y2, float z2);
		static void alpha_beta_to_cartesian(float x1, float y1, float x2, float y2, float percent, float* outx, float* outy);
		static bool process_intersection(float* p, float* d, float* v0, float* v1, float* v2, float* t);
	public:
		static bool get_intersection(vertex* ray, triangle* tri, vertex* intersect);
		static void transform_trace_to_uv(triangle* t, vertex* hit);
};

#endif
