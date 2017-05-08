#ifndef _GEOMETRY_CUH
#define _GEOMETRY_CUH

struct vertex
{
	float x; //World position.
	float y;
	float z;
	float nx; //Surface normal.
	float ny;
	float nz;
	float u; //Texture coordinates.
	float v;
	__device__ __host__ vertex(float pos_x, float pos_y, float pos_z, float normal_x, float normal_y, float normal_z, float tex_x, float tex_y);
	__device__ __host__ vertex(float pos_x, float pos_y, float pos_z);
	__device__ __host__ vertex();
	__device__ __host__ ~vertex();
};

struct triangle
{
	vertex* v[3];
	__device__ __host__ triangle(vertex* v1, vertex* v2, vertex* v3);
	__device__ __host__ ~triangle();
};

#endif
