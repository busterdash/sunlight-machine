#ifndef _RAYTRACER_CUH
#define _RAYTRACER_CUH

#include "geometry.cuh"

class raytracer
{
	private:
		__device__ __host__ static void vec(float* a, float* b, float* c);
		__device__ __host__ static void cross_product(float* a, float* b, float* c);
		__device__ __host__ static float dot_product(float* a, float* b);
		__device__ __host__ static float distance_formula_3d(float x1, float y1, float z1, float x2, float y2, float z2);
		__device__ __host__ static void alpha_beta_to_cartesian(float x1, float y1, float x2, float y2, float percent, float* outx, float* outy);
		__device__ __host__ static bool process_intersection(float* p, float* d, float* v0, float* v1, float* v2, float* t);
	public:
		__device__ __host__ static bool get_intersection(vertex* ray, triangle* tri, vertex* intersect, float* dist);
		__device__ __host__ static void transform_trace_to_uv(triangle* t, vertex* hit);
};

#endif
